#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <ctime>
#include <iterator>
#include <random>

#include "constants.h"

inline auto random_engine() noexcept -> std::mt19937&
{
  static std::mt19937 gen(static_cast<std::size_t>(time(NULL)));
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
  return std::max(generated, 1);
}

/* {{{ doc */
/**
 * @brief Randomly selects one element from the range defined by
 * [begin,end).
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
auto random_select(Itr begin, const Itr end) noexcept -> Itr
{
  auto size {std::distance(begin, end)};

  // using (size - 1) to avoid indexing out-of-bounds
  std::uniform_int_distribution<decltype(size)> selection_dist(0,
                                                               size - 1);

  std::advance(begin, selection_dist(random_engine()));

  return begin;
}

#endif
