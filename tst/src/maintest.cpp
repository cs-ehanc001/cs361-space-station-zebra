#include "test_queue.h"
#include "test_utils.hpp"

auto main([[maybe_unused]] const int argc,
          [[maybe_unused]] const char* const* const argv) -> int
{

  ehanc::test_section("Queue", &test_queue);

  return 0;
}
