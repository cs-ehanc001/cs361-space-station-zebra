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

  for ( std::size_t i {0}; i < num_samples; ++i ) {
    test_values.push_back(static_cast<long>(get_part_count()));
  }

  double test_values_mean {
      static_cast<double>(
          std::accumulate(test_values.cbegin(), test_values.cend(), 0L))
      / static_cast<double>(num_samples)};

  double mean_diff {
      std::abs(test_values_mean - conf::broken_part_count_mean)};

  // Testing for being within 0.5 of mean, because requiring a minimum of 1
  // drags down the mean
  std::string mean_test_msg {
      "Measured mean not within 0.5 of expected, actual mean diff == "};
  mean_test_msg += std::to_string(mean_diff);

  results.add_case(mean_diff < 0.5, true, mean_test_msg);
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

auto test_random_select() -> ehanc::test
{
  ehanc::test results;

  const int range_max {20};
  const std::size_t num_samples {1'000'000};

  // Fudge factor for how often a particular value is selected
  // Any element may be selected
  // ((num_samples / range_max) +- count_fudge_factor) times
  const int count_fudge_factor {700};

  std::vector<int> range(range_max);
  std::iota(range.begin(), range.end(),
            1); // fill range with [1, range_max]

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

void test_random()
{
  ehanc::run_test("get_part_count", &test_get_part_count);
  ehanc::run_test("random_select", &test_random_select);
}
