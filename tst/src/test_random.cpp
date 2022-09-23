#include <algorithm>
#include <deque>
#include <string>

#include "constants.h"
#include "test_random.h"
#include "test_utils.hpp"

auto test_get_part_count() -> ehanc::test
{
  ehanc::test results;

  using test_value_t = long;

  std::deque<test_value_t> test_values;

  const std::size_t num_samples {1000000};

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

void test_random()
{
  ehanc::run_test("get_part_count", &test_get_part_count);
}
