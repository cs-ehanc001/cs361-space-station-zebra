#include <algorithm>
#include <numeric>
#include <vector>

#include "utils/algorithm.hpp"

#include "random.hpp"
#include "ship.h"

template <typename Itr>
static auto
create_damaged_part_list_helper(const Itr begin, const Itr end,
                                const int severity_min,
                                const int severity_max) noexcept
    -> std::list<ship::part>
{
  std::size_t broken_part_count {
      static_cast<std::size_t>(get_part_count())};

  std::vector<int> selected_part_ids;

  selected_part_ids.emplace_back(*random_select(begin, end));

  while ( selected_part_ids.size() != broken_part_count ) {
    int selected_id {*random_select(begin, end)};

    // if selected_id not already in selected_part_ids
    if ( !ehanc::contains(selected_part_ids.cbegin(),
                          selected_part_ids.cend(), selected_id) ) {
      selected_part_ids.push_back(selected_id);
    }
  }

  std::uniform_int_distribution sev_dist(severity_min, severity_max);

  std::list<ship::part> retval;

  std::for_each(selected_part_ids.cbegin(), selected_part_ids.cend(),
                [&retval, &sev_dist](int id) noexcept {
                  retval.emplace_back(id, sev_dist(random_engine()));
                });

  return retval;
}

auto ship::create_damaged_part_list(ship::faction fact) noexcept
    -> std::list<ship::part>
{
  switch ( fact ) {

  case faction::human:

    return create_damaged_part_list_helper(
        conf::human_part_list.cbegin(), conf::human_part_list.cend(),
        conf::human_severity_min, conf::human_severity_max);

  case faction::ferengi:

    return create_damaged_part_list_helper(
        conf::ferengi_part_list.cbegin(), conf::ferengi_part_list.cend(),
        conf::ferengi_severity_min, conf::ferengi_severity_max);

  case faction::klingon:

    return create_damaged_part_list_helper(
        conf::klingon_part_list.cbegin(), conf::klingon_part_list.cend(),
        conf::klingon_severity_min, conf::klingon_severity_max);

  case faction::romulan:

    return create_damaged_part_list_helper(
        conf::romulan_part_list.cbegin(), conf::romulan_part_list.cend(),
        conf::romulan_severity_min, conf::romulan_severity_max);

  case faction::other:

    return create_damaged_part_list_helper(
        conf::other_part_list.cbegin(), conf::other_part_list.cend(),
        conf::other_severity_min, conf::other_severity_max);

  default:

    // should not be reachable
    return {};
  }
}

auto ship::construct_random_ship() noexcept -> ship
{
  faction random_faction {get_random_faction()};

  return {random_faction};
}

auto ship::get_total_damage() const noexcept -> int
{
  if ( this->is_damaged() ) {
    return std::accumulate(
        m_damaged_parts.cbegin(), m_damaged_parts.cend(), 0,
        [](int acc, const part arg) noexcept { return acc + arg.damage; });
  } else {
    return 0;
  }
}
