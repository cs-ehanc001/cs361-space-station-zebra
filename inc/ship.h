#ifndef SHIP_H
#define SHIP_H

#include <list>

#include "constants.h"

class ship
{
public:

  enum class faction { human, ferengi, klingon, romulan, other };

  struct part {
    int id;
    int damage;

    part(int id_arg, int damage_arg)
        : id(id_arg)
        , damage(damage_arg)
    {}
  };

private:

  int m_id;

  faction m_faction;

  std::list<part> m_damaged_parts;

  /* {{{ doc */
  /**
   * @brief Creates a valid damaged part list for a faction.
   *
   * @param fact Faction for which to create a list of valid damaged parts
   */
  /* }}} */
  static auto create_damaged_part_list(faction fact) noexcept
      -> std::list<part>;

public:

  ship() = delete;

  ship(faction fact) noexcept
      : m_id {}
      , m_faction {fact}
      , m_damaged_parts {create_damaged_part_list(fact)}
  {
    static int next_id {conf::starting_ship_id};
    m_id = next_id;
    ++next_id;
  }

  ship(const ship& src) noexcept;

  auto operator=(const ship& rhs) noexcept -> ship&;

  ship(ship&& src) noexcept;

  auto operator=(ship&& rhs) noexcept -> ship&;

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

  inline auto get_faction() const noexcept -> faction
  {
    return m_faction;
  }

  inline auto get_damaged_part_count() const noexcept -> std::size_t
  {
    return m_damaged_parts.size();
  }

  inline auto get_id() const noexcept -> int
  {
    return m_id;
  }
};

#endif
