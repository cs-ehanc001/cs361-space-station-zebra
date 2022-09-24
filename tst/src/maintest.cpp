#include "test_utils.hpp"

#include "test_random.h"
#include "test_ship.h"

auto main() -> int
{

  ehanc::test_section("Random", &test_random);

  ehanc::test_section("Ship", &test_ship);

  return 0;
}
