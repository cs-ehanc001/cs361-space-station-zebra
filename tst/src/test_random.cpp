#include <algorithm>
#include <deque>
#include <numeric>
#include <sstream>
#include <string>

#include "utils/etc.hpp"

#include "constants.h"
#include "test_random.h"
#include "test_utils.hpp"

auto test_get_part_count() -> ehanc::test
{
  ehanc::test results;

  using test_value_t = long;

  std::deque<test_value_t> test_values;

  const std::size_t num_samples {1'000'000};

  const double mean_fudge_factor {0.5};

  for ( std::size_t i {0}; i < num_samples; ++i ) {
    test_values.push_back(static_cast<long>(get_part_count()));
  }

  double test_values_mean {
      static_cast<double>(
          std::accumulate(test_values.cbegin(), test_values.cend(), 0L))
      / static_cast<double>(num_samples)};

  double mean_diff {
      std::abs(test_values_mean - conf::broken_part_count_mean)};

  // Testing for being within mean_fudge_factor of mean, because requiring
  // a minimum of 1 drags down the mean
  std::string mean_test_msg {
      "Measured mean not within" + std::to_string(mean_fudge_factor)
      + "of expected, actual mean diff == " + std::to_string(mean_diff)};

  results.add_case(mean_diff < mean_fudge_factor, true, mean_test_msg);
  results.add_case(test_values_mean < conf::broken_part_count_mean, true,
                   "Mean not dragged down");

  using diff_t = typename std::iterator_traits<
      std::deque<test_value_t>::const_iterator>::difference_type;

  diff_t num_bad_values {
      std::count_if(test_values.cbegin(), test_values.cend(),
                    [](const test_value_t val) -> bool {
                      return val < conf::broken_part_count_min;
                    })};

  results.add_case(
      num_bad_values, static_cast<diff_t>(0),
      "Returned a value less than conf::broken_part_count_min");

  return results;
}

auto test_get_new_ship_count() noexcept -> ehanc::test
{
  ehanc::test results;

  using test_value_t = double;
  std::deque<test_value_t> test_values;
  const std::size_t num_samples {3'000'000};

  const double mean_fudge_factor {0.0005};

  for ( std::size_t i {0}; i < num_samples; ++i ) {
    test_values.push_back(static_cast<double>(get_new_ship_count()));
  }

  double test_values_mean {
      static_cast<double>(
          std::accumulate(test_values.cbegin(), test_values.cend(), 0.0))
      / static_cast<double>(num_samples)};

  double mean_diff {
      std::abs(test_values_mean - conf::new_ship_count_poisson_mean)};

  std::string mean_test_msg {
      "Measured mean not within" + std::to_string(mean_fudge_factor)
      + "of expected, actual mean diff == " + std::to_string(mean_diff)};

  results.add_case(mean_diff < mean_fudge_factor, true, mean_test_msg);

  return results;
}

auto test_random_select() -> ehanc::test
{
  ehanc::test results;

  const int range_max {20};
  const std::size_t num_samples {1'000'000};

  // Fudge factor for how often a particular value is selected
  // Any element may be selected
  // ((num_samples / range_max) +- count_fudge_factor) times
  const int count_fudge_factor {800};

  // fill range with [1, range_max]
  std::vector<int> range(range_max);
  std::iota(range.begin(), range.end(), 1);

  std::deque<int> samples;
  for ( std::size_t i {0}; i < num_samples; ++i ) {
    samples.push_back(*random_select(range.cbegin(), range.cend()));
  }

  using count_t = typename std::iterator_traits<
      std::vector<int>::const_iterator>::difference_type;

  for ( const auto val : range ) {
    // Number of times val occures in samples
    count_t num_occurances {
        std::count(samples.cbegin(), samples.cend(), val)};
    count_t expected_occurances {num_samples / range_max};

    std::stringstream message;
    message << "Expected " << expected_occurances << " +- "
            << count_fudge_factor << " occurances of " << val << ", got "
            << num_occurances << " occurances.";

    bool is_good_count {std::abs(expected_occurances - num_occurances)
                        < count_fudge_factor};

    results.add_case(is_good_count, true, message.str());
  }

  return results;
}

auto test_get_random_faction() -> ehanc::test
{
  ehanc::test results;

  const int num_samples {1'000'000};
  const double chance_fudge_factor {1.5};

  using count_t = typename std::iterator_traits<
      std::deque<ship::faction>::const_iterator>::difference_type;
  std::deque<ship::faction> samples;

  for ( std::size_t i {0}; i < num_samples; ++i ) {
    samples.push_back(get_random_faction());
  }

  const count_t human_count {
      std::count(samples.cbegin(), samples.cend(), ship::faction::human)};
  const count_t ferengi_count {std::count(samples.cbegin(), samples.cend(),
                                          ship::faction::ferengi)};
  const count_t klingon_count {std::count(samples.cbegin(), samples.cend(),
                                          ship::faction::klingon)};
  const count_t romulan_count {std::count(samples.cbegin(), samples.cend(),
                                          ship::faction::romulan)};
  const count_t other_count {
      std::count(samples.cbegin(), samples.cend(), ship::faction::other)};

  auto case_adder {[&](const count_t count, const ship::faction type,
                       int expected_chance) {
    auto faction_to_string {
        [](const ship::faction fact) -> std::string_view {
          switch ( fact ) {
          case ship::faction::human:
            return "human";
          case ship::faction::ferengi:
            return "ferengi";
          case ship::faction::klingon:
            return "klingon";
          case ship::faction::romulan:
            return "romulan";
          case ship::faction::other:
            return "other";
          default:
            return "Something has gone horribly wrong";
          }
        }};

    double apparent_chance {
        (static_cast<double>(count) / static_cast<double>(num_samples))
        * 100};

    std::stringstream message;
    message << "Expected " << expected_chance << "% "
            << faction_to_string(type) << ", but got " << apparent_chance
            << "%";

    bool is_good_chance {
        std::abs(static_cast<double>(expected_chance) - apparent_chance)
        < chance_fudge_factor};

    results.add_case(is_good_chance, true, message.str());
  }};

  case_adder(human_count, ship::faction::human, conf::human_ship_chance);
  case_adder(ferengi_count, ship::faction::ferengi,
             conf::ferengi_ship_chance);
  case_adder(klingon_count, ship::faction::klingon,
             conf::klingon_ship_chance);
  case_adder(romulan_count, ship::faction::romulan,
             conf::romulan_ship_chance);
  case_adder(other_count, ship::faction::other, conf::other_ship_chance);

  return results;
}

void test_random()
{
  ehanc::run_test("get_part_count", &test_get_part_count);
  ehanc::run_test("get_new_ship_count", &test_get_new_ship_count);
  ehanc::run_test("random_select", &test_random_select);
  ehanc::run_test("get_random_faction", &test_get_random_faction);
}
