#ifndef SHIP_H
#define SHIP_H

#include <numeric>

#include "constants.h"
#include "list.hpp"

namespace zebra {

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

  void p_create_damage();

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
  inline auto get_total_damage() const noexcept -> int
  {
    if ( this->is_damaged() ) {
      return std::accumulate(m_damaged_parts.cbegin(),
                             m_damaged_parts.cend(), 0,
                             [](int acc, const part arg) noexcept {
                               return acc + arg.damage;
                             });
    } else {
      return 0;
    }
  }

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

} // namespace zebra

#endif
