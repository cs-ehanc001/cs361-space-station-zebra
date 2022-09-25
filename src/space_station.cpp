#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

#include "utils/etc.hpp"

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
    const bool ship_left_bay {bay.step()};
    if ( bay.empty() ) {
      if ( this->queue_size() != 0 ) {
        bay.dock(std::move(m_repair_queue.front()));
        m_repair_queue.pop();
      }
      if ( ship_left_bay ) {
        ++exiting_ship_count;
      }
    }
  }

  // increase internal counter
  ++m_step_count;

  m_last_step_summary = step_summary {new_ship_count, exiting_ship_count};

  return m_last_step_summary;
}

void space_station::display(std::ostream& out) const noexcept
{
  out << conf::header_line << '\n';
  for ( int i {0}; i != conf::header_line.length() / 4; ++i ) {
    out << ' ';
  }
  out << m_name << "'s report for hour " << m_step_count << '\n';
  out << conf::header_line << '\n' << '\n';

  out << m_last_step_summary.new_ships << " ships arrived, "
      << m_last_step_summary.leaving_ships << " ships exited." << '\n'
      << '\n';

  std::for_each(m_bays.cbegin(), m_bays.cend(),
                [&out, index {0}](const repair_bay& bay) mutable {
                  out << "Repair Bay #" << ++index << "'s report:\n"
                      << bay << '\n';
                });

  out << '\n';

  if ( this->queue_size() > 2 ) {
    out << "Queue status: " << this->queue_size() << " ships."
        << " Front and back of queue:\n\n"
        << m_repair_queue.front() << '\n'
        << m_repair_queue.back() << '\n'
        << '\n';
  } else if ( this->queue_size() == 1 ) {
    out << "Queue status: 1 ship. Member is:\n\n"
        << m_repair_queue.front() << '\n'
        << '\n';
  } else {
    out << "Queue status: 0 ships.\n\n\n";
  }
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
