#ifndef SPACE_STATION_H
#define SPACE_STATION_H

#include <array>
#include <cstddef>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

#include "constants.h"
#include "repair_bay.h"
#include "ship.h"

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class space_station
{
public:

  struct step_summary {
    std::size_t new_ships;
    std::size_t leaving_ships;
  };

private:

  std::vector<repair_bay> m_bays;

  // Only using a deque instead of a queue so that I can
  // print it to the output
  std::queue<ship> m_repair_queue {};
  std::size_t m_step_count {};
  step_summary m_last_step_summary {};
  std::string m_name {"Zebra"};

public:

  space_station(std::string_view name,
                std::size_t bay_count = conf::num_repair_bays) noexcept
      : m_bays(bay_count)
      , m_repair_queue {}
      , m_step_count {}
      , m_last_step_summary {}
      , m_name(name)
  {}

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
  [[nodiscard]] inline auto queue_size() const noexcept -> std::size_t
  {
    return m_repair_queue.size();
  }

  /* {{{ doc */
  /**
   * @brief Returns number of time steps that have occured.
   */
  /* }}} */
  [[nodiscard]] inline auto step_count() const noexcept -> std::size_t
  {
    return m_step_count;
  }

  void display(std::ostream& out) const noexcept;

  /* {{{ doc */
  /**
   * @brief Return number of empty repair bays.
   */
  /* }}} */
  [[nodiscard]] auto empty_bay_count() const noexcept -> int;

  /* {{{ doc */
  /**
   * @brief Return number of occupied repair bays.
   */
  /* }}} */
  [[nodiscard]] auto occupied_bay_count() const noexcept -> int;
};

#endif
