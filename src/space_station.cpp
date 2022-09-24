#include <algorithm>
#include <vector>

#include "random.hpp"
#include "space_station.h"

auto space_station::step() noexcept -> step_summary
{
  const std::size_t new_ship_count {
      static_cast<std::size_t>(get_new_ship_count())};

  // new ships get in line
  for ( std::size_t i {0}; i != new_ship_count; ++i ) {
    m_repair_queue.push(ship::construct_random_ship());
  }

  std::size_t exiting_ship_count {0};

  // all bays step (tick down timer, clear if done), then,
  // if empty, dock next in line
  for ( repair_bay& bay : m_bays ) {
    bay.step();
    if ( bay.empty() ) {
      bay.dock(std::move(m_repair_queue.front()));
      m_repair_queue.pop();
      ++exiting_ship_count;
    }
  }

  // increase internal counter
  ++m_step_count;

  return {new_ship_count, exiting_ship_count};
}

auto space_station::empty_bay_count() const noexcept -> int
{
  return static_cast<int>(
      std::count_if(m_bays.cbegin(), m_bays.cend(),
                    [](const repair_bay& bay) { return bay.empty(); }));
}

auto space_station::occupied_bay_count() const noexcept -> int
{
  return static_cast<int>(std::count_if(
      m_bays.cbegin(), m_bays.cend(),
      [](const repair_bay& bay) { return not bay.empty(); }));
}
