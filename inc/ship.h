#ifndef SHIP_H
#define SHIP_H

#include <numeric>

#include "constants.h"
#include "list.hpp"
#include "random.h"

class ship
{
public:

  enum class faction { human, ferengi, klingon, romulan, other };

private:

  struct part {
    int id;
    int damage;
  };

  int m_id;

  faction m_faction;

  ehanc::list<part> m_damaged_parts;

  static auto get_damaged_part_list(faction fact) noexcept
      -> ehanc::list<part>;

public:

  ship() = delete;

  ship(faction fact)
      : m_id {}
      , m_faction {fact}
      , m_damaged_parts {get_damaged_part_list(fact)}
  {
    static int next_id {conf::starting_ship_id};
    m_id = next_id;
    ++next_id;
  }

  ship(const ship& src) noexcept;

  auto operator=(const ship& rhs) -> ship& noexcept;

  ship(ship&& src) noexcept;

  auto operator=(ship&& rhs) -> ship& noexcept;

  ~ship() noexcept = default;

  /* {{{ doc */
  /**
   * @brief Get sum of all damage values of all parts.
   */
  /* }}} */
  auto get_total_damage() const noexcept -> int;

  /* {{{ doc */
  /**
   * @brief Determines if ship is damaged.
   */
  /* }}} */
  inline auto is_damaged() const noexcept -> bool
  {
    return m_damaged_parts.size() == 0;
  }

  /* {{{ doc */
  /**
   * @brief Clears list of damaged parts.
   */
  /* }}} */
  inline void repair() noexcept
  {
    m_damaged_parts.clear();
  }
};

#endif
