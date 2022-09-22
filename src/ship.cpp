#include "ship.h"

auto ship::get_total_damage() const noexcept -> int
{
  if ( this->is_damaged() ) {
    return std::accumulate(
        m_damaged_parts.cbegin(), m_damaged_parts.cend(), 0,
        [](int acc, const part arg) noexcept { return acc + arg.damage; });
  } else {
    return 0;
  }
}

auto ship::get_damaged_part_list(faction fact) noexcept
    -> ehanc::list<part>
{}
