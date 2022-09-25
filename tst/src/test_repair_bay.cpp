#include <algorithm>
#include <utility>
#include <vector>

#include "test_repair_bay.h"
#include "test_utils.hpp"

static auto test_dock() -> ehanc::test
{
  ehanc::test results;

  const int sample_size {1'000};

  repair_bay test;
  std::vector<ship> sample_ships;
  sample_ships.reserve(sample_size);
  std::generate(sample_ships.begin(), sample_ships.end(),
                &ship::construct_random_ship);

  auto test_helper {[&](ship&& sample) {
    const int ship_repair_time {
        conf::severity_to_time(sample.get_total_damage())};

    results.add_case(test.has_ship(), false,
                     "Reports having ship when should not");
    results.add_case(test.empty(), true,
                     "Does not report being empty when should");
    results.add_case(test.time_remaining(), 0);

    test.dock(std::move(sample));

    results.add_case(test.has_ship(), true,
                     "Reports not having ship when should");
    results.add_case(test.empty(), false,
                     "Reports being empty when should not");
    results.add_case(test.time_remaining(), ship_repair_time,
                     "Inaccurate time remaining");
  }};

  for ( ship& sample : sample_ships ) {
    test_helper(std::move(sample));
  }

  return results;
}

static auto test_step() -> ehanc::test
{
  ehanc::test results;

  const int sample_size {1'000};

  repair_bay test;
  std::vector<ship> sample_ships;
  sample_ships.reserve(sample_size);
  std::generate(sample_ships.begin(), sample_ships.end(),
                &ship::construct_random_ship);

  auto test_helper {[&](ship&& sample) {
    const int ship_repair_time {
        conf::severity_to_time(sample.get_total_damage())};

    for ( int i {ship_repair_time}; i != 0; --i ) {
      results.add_case(test.time_remaining(), i, "Bad time remaining");
      test.step();
    }

    results.add_case(test.time_remaining(), 0, "Bad time remaining");
    results.add_case(test.empty(), true, "Not reporting empty");
    results.add_case(test.has_ship(), false, "Reporting has ship");
  }};

  for ( ship& sample : sample_ships ) {
    test_helper(std::move(sample));
  }

  return results;
}

void test_repair_bay()
{
  ehanc::run_test("repair_bay::dock", &test_dock);
  ehanc::run_test("repair_bay::step", &test_step);
}
