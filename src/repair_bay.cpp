#include <utility>

#include "repair_bay.h"

void repair_bay::dock(ship&& incoming_ship) noexcept
{
  m_docked_ship.emplace(std::move(incoming_ship));
  m_remaining_repair_time =
      conf::severity_to_time(m_docked_ship->get_total_damage());
}

void repair_bay::step() noexcept
{
  if ( m_remaining_repair_time != 0 ) {
    --m_remaining_repair_time;
  }

  if ( m_remaining_repair_time == 0 ) {
    m_docked_ship.reset();
  }
}
