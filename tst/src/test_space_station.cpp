#include <utility>

#include "utils/etc.hpp"

#include "test_space_station.h"
#include "test_utils.hpp"

#include "constants.h"

static auto test_step() -> ehanc::test
{
  using namespace ehanc::literals::size_t_literal;

  ehanc::test results;

  space_station test;

  results.add_case(test.empty_bay_count(), conf::num_repair_bays,
                   "Bays not all empty");
  results.add_case(test.queue_size(), 0_z, "Queue not starting empty");

  const std::size_t num_sample_steps {5};

  std::size_t expected_num_ships_in_station {0};
  std::size_t actual_num_ships_in_station {0};

  for ( std::size_t i {0}; i != num_sample_steps; ++i ) {
    auto [arrivals, finished] = test.step();

    expected_num_ships_in_station =
        expected_num_ships_in_station + arrivals - finished;

    actual_num_ships_in_station =
        test.queue_size()
        + static_cast<std::size_t>(test.occupied_bay_count());

    results.add_case(actual_num_ships_in_station,
                     expected_num_ships_in_station,
                     "Wrong number of ships at the station");
  }

  return results;
}

void test_space_station()
{
  ehanc::run_test("space_station::step", &test_step);
}
