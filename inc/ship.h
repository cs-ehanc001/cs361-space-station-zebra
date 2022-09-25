#ifndef SHIP_H
#define SHIP_H

#include <cstddef>
#include <iostream>
#include <list>
#include <string>

#include "constants.h"

class ship
{
public:

  enum class faction { human, ferengi, klingon, romulan, other };

  struct part {
    int id;
    int damage;

    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    part(int id_arg, int damage_arg) // It must be this way
        : id(id_arg)
        , damage(damage_arg)
    {}
  };

private:

  int m_id;

  faction m_faction;

  std::list<part> m_damaged_parts;

public:

  /* {{{ doc */
  /**
   * @brief Creates a valid damaged part list for a faction.
   *
   * @param fact Faction for which to create a list of valid damaged parts
   */
  /* }}} */
  static auto create_damaged_part_list(faction fact) noexcept
      -> std::list<part>;

  ship() = delete;

  /* {{{ doc */
  /**
   * @brief Ensures a ship is constructed in a valid state.
   * A valid state being: having the next ID number,
   * having a faction, and beginning in a damaged state.
   * However, constructing with ship::construct_random_ship() is
   * greatly preferred.
   *
   * @param fact Faction of the ship to construct.
   */
  /* }}} */
  ship(faction fact) noexcept
      : m_id {}
      , m_faction {fact}
      , m_damaged_parts {create_damaged_part_list(fact)}
  {
    static int next_id {conf::starting_ship_id};
    m_id = next_id;
    ++next_id;
  }

  ship(const ship& src) noexcept = delete;

  auto operator=(const ship& rhs) -> ship& = delete;

  ship(ship&& src) = default;

  auto operator=(ship&& rhs) noexcept -> ship& = default;

  ~ship() noexcept = default;

  static auto construct_random_ship() noexcept -> ship;

  void display(std::ostream& out) const noexcept;

  /* {{{ doc */
  /**
   * @brief Get sum of all damage values of all parts.
   */
  /* }}} */
  [[nodiscard]] auto get_total_damage() const noexcept -> int;

  /* {{{ doc */
  /**
   * @brief Determines if ship is damaged.
   */
  /* }}} */
  [[nodiscard]] inline auto is_damaged() const noexcept -> bool
  {
    return not m_damaged_parts.empty();
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

  [[nodiscard]] inline auto get_faction() const noexcept -> faction
  {
    return m_faction;
  }

  [[nodiscard]] inline auto get_damaged_part_count() const noexcept
      -> std::size_t
  {
    return m_damaged_parts.size();
  }

  [[nodiscard]] inline auto get_id() const noexcept -> int
  {
    return m_id;
  }

  [[nodiscard]] inline auto get_damaged_parts_list() const noexcept
      -> const std::list<part>&
  {
    return m_damaged_parts;
  }
};

inline auto operator<<(std::ostream& out, const ship& rhs) noexcept
    -> std::ostream&
{
  rhs.display(out);
  return out;
}

#endif
