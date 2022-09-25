#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <algorithm>
#include <cstddef>
#include <ctime>
#include <iterator>
#include <random>
#include <type_traits>

#include "constants.h"
#include "ship.h"

inline auto random_engine() noexcept -> conf::random_engine&
{
  static conf::random_engine gen(static_cast<std::size_t>(time(nullptr)));
  return gen;
}

/* {{{ doc */
/**
 * @brief Returns a valid count of broken parts. Normal distribution
 * paramaters defined in `constants.h`, through
 * `conf::broken_part_count_mean` and `conf::broken_part_count_stddev`.
 */
/* }}} */
inline auto get_part_count() noexcept -> int
{
  static std::normal_distribution<double> broken_part_dist(
      conf::broken_part_count_mean, conf::broken_part_count_stddev);

  int generated {static_cast<int>(broken_part_dist(random_engine()))};

  // ensure return value >= 1
  return std::max(generated, conf::broken_part_count_min);
}

inline auto get_new_ship_count() noexcept -> int
{
  static std::poisson_distribution<int> new_ship_dist(
      conf::new_ship_count_poisson_mean);

  return new_ship_dist(random_engine());
}

/* {{{ doc */
/**
 * @brief Randomly selects one element from the range defined by
 * [begin,end). Selection is done with a uniform distribution.
 *
 * @tparam Itr Any iterator type.
 *
 * @param begin Beginning of range.
 *
 * @param end End of range
 *
 * @return Iterator to selected element.
 */
/* }}} */
template <typename Itr>
inline auto random_select(Itr begin, const Itr end) noexcept -> Itr
{
  // expected to be std::ptrdiff_t
  // on my systems (64-bit Linux, amd64, libstdc++-11 and libstdc++-12,
  // g++-11 and g++-12 in std=c++17) that type is long
  using itrdiff_t = typename std::iterator_traits<Itr>::difference_type;

  itrdiff_t size {std::distance(begin, end)};

  // using (size - 1) to avoid indexing out-of-bounds
  std::uniform_int_distribution<itrdiff_t> selection_dist(0, size - 1);

  std::advance(begin, selection_dist(random_engine()));

  return begin;
}

/* {{{ doc */
/**
 * @brief Returns a random faction weighted accordingly to
 * `conf::*_ship_chance` constants in constants.h
 */
/* }}} */
inline auto get_random_faction() -> ship::faction
{
  std::uniform_int_distribution fact_dist(1, 100);

  int random {fact_dist(random_engine())};

  if ( random < conf::human_ship_chance ) {

    // 50% chance
    return ship::faction::human;

  } else if ( random
              < conf::human_ship_chance + conf::ferengi_ship_chance ) {

    // 65 - 50 = 50% chance
    return ship::faction::ferengi;

  } else if ( random < conf::human_ship_chance + conf::ferengi_ship_chance
                           + conf::klingon_ship_chance ) {

    // 75 - 65 = 10% chance
    return ship::faction::klingon;

  } else if ( random < conf::human_ship_chance + conf::ferengi_ship_chance
                           + conf::klingon_ship_chance
                           + conf::romulan_ship_chance ) {

    // 80 - 75 = 5% chance
    return ship::faction::romulan;

  } else {

    // 100 - 80 = 20% chance
    return ship::faction::other;
  }
}

#endif
