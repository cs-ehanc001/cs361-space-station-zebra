#include <iostream>
#include <utility>

#include "repair_bay.h"

void repair_bay::dock(ship&& incoming_ship) noexcept
{
  m_docked_ship.emplace(std::move(incoming_ship));
  m_remaining_repair_time =
      conf::severity_to_time(m_docked_ship->get_total_damage());
}

void repair_bay::display(std::ostream& out) const noexcept
{
  if ( this->empty() ) {
    out << "Repair bay is empty." << '\n';
    return;
  } else {
    out << "Repair bay has docked: " << *m_docked_ship
        << "  Ship requires " << this->time_remaining()
        << " more hours to repair.\n";
    return;
  }
}

auto repair_bay::step() noexcept -> bool
{
  if ( m_remaining_repair_time != 0 ) {
    // ship in repair bay
    --m_remaining_repair_time;
    if ( m_remaining_repair_time == 0 ) {
      // repairs completed
      m_docked_ship.reset();
      return true; // ship left this time step
    }
  }
  // repair bay did nothing this time step
  return false;
}
