#include "random.h"

#include <ctime>

auto random_engine() noexcept -> std::mt19937&
{
  static std::mt19937 gen(static_cast<std::size_t>(time(NULL)));
  return gen;
}

