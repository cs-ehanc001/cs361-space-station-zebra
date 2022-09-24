#ifndef REPAIR_BAY_H
#define REPAIR_BAY_H

#include <optional>

#include "constants.h"
#include "ship.h"

class repair_bay
{
private:

  std::optional<ship> m_docked_ship {};
  int m_remaining_repair_time {};

public:

  repair_bay() = default;

  /* {{{ doc */
  /**
   * @brief Must not be copied
   */
  /* }}} */
  repair_bay(const repair_bay& src) = delete;

  /* {{{ doc */
  /**
   * @brief Must not be copied
   */
  /* }}} */
  auto operator=(const repair_bay& rhs) -> repair_bay& = delete;

  /* {{{ doc */
  /**
   * @brief Must not be moved
   */
  /* }}} */
  repair_bay(repair_bay&& src) = delete;

  /* {{{ doc */
  /**
   * @brief Must not be moved
   */
  /* }}} */
  auto operator=(repair_bay&& rhs) -> repair_bay& = delete;

  ~repair_bay() = default;

  /* {{{ doc */
  /**
   * @brief Accept a ship, and move into repair bay
   */
  /* }}} */
  void dock(ship&& incoming_ship) noexcept;

  /* {{{ doc */
  /**
   * @brief Perform one time step - continue repairs, and send
   * ship away if repaired
   */
  /* }}} */
  void step() noexcept;

  /* {{{ doc */
  /**
   * @brief Determine if there is a ship docked
   */
  /* }}} */
  [[nodiscard]] inline auto has_ship() const noexcept -> bool
  {
    return m_docked_ship.has_value();
  }

  /* {{{ doc */
  /**
   * @brief Determine if repair bay is empty
   */
  /* }}} */
  [[nodiscard]] inline auto empty() const noexcept -> bool
  {
    return not this->has_ship();
  }

  /* {{{ doc */
  /**
   * @brief Get remaining repair time
   */
  /* }}} */
  [[nodiscard]] inline auto time_remaining() const noexcept -> int
  {
    return m_remaining_repair_time;
  }
};

#endif
