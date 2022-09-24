#ifndef SPACE_STATION_H
#define SPACE_STATION_H

#include <array>
#include <queue>

#include "constants.h"
#include "repair_bay.h"
#include "ship.h"

class space_station
{
private:

  std::array<repair_bay, conf::num_repair_bays> m_bays {};
  std::queue<ship> m_repair_queue {};
  std::size_t m_step_count {};

public:

  struct step_summary {
    std::size_t new_ships;
    std::size_t leaving_ships;
  };

  space_station() = default;

  /* {{{ doc */
  /**
   * @brief Must not be copied
   */
  /* }}} */
  space_station(const repair_bay& src) = delete;

  /* {{{ doc */
  /**
   * @brief Must not be copied
   */
  /* }}} */
  auto operator=(const space_station& rhs) -> repair_bay& = delete;

  /* {{{ doc */
  /**
   * @brief Must not be moved
   */
  /* }}} */
  space_station(repair_bay&& src) = delete;

  /* {{{ doc */
  /**
   * @brief Must not be moved
   */
  /* }}} */
  auto operator=(space_station&& rhs) -> repair_bay& = delete;

  ~space_station() = default;

  /* {{{ doc */
  /**
   * @brief Simulate one time step. New ships are generated,
   * all occupied bays tick down, bays clear out if done, empty bays
   * accept the next in line, in that order.
   */
  /* }}} */
  auto step() noexcept -> step_summary;

  /* {{{ doc */
  /**
   * @brief Return size of internal queue.
   */
  /* }}} */
  inline auto queue_size() const noexcept -> std::size_t
  {
    return m_repair_queue.size();
  }

  /* {{{ doc */
  /**
   * @brief Returns number of time steps that have occured.
   */
  /* }}} */
  inline auto step_count() const noexcept -> std::size_t
  {
    return m_step_count;
  }

  /* {{{ doc */
  /**
   * @brief Return number of empty repair bays.
   */
  /* }}} */
  auto empty_bay_count() const noexcept -> int;

  /* {{{ doc */
  /**
   * @brief Return number of occupied repair bays.
   */
  /* }}} */
  auto occupied_bay_count() const noexcept -> int;
};

#endif
