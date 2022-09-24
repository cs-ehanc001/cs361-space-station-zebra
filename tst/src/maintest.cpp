#include "test_utils.hpp"

#include "test_random.h"
#include "test_repair_bay.h"
#include "test_ship.h"
#include "test_space_station.h"

auto main() -> int
{

  ehanc::test_section("Random", &test_random);

  ehanc::test_section("Ship", &test_ship);

  ehanc::test_section("Repair Bay", &test_repair_bay);

  ehanc::test_section("Space Station", &test_space_station);

  return 0;
}
