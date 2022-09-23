#include <vector>

#include "utils/algorithm.hpp"

#include "test_ship.h"
#include "test_utils.hpp"

auto test_create_damaged_part_list() -> ehanc::test
{
  ehanc::test results;

  const std::list<ship::part> human_list {
      ship::create_damaged_part_list(ship::faction::human)};
  const std::list<ship::part> ferengi_list {
      ship::create_damaged_part_list(ship::faction::ferengi)};
  const std::list<ship::part> klingon_list {
      ship::create_damaged_part_list(ship::faction::klingon)};
  const std::list<ship::part> romulan_list {
      ship::create_damaged_part_list(ship::faction::romulan)};
  const std::list<ship::part> other_list {
      ship::create_damaged_part_list(ship::faction::other)};

  // get_part_count() and random_select() already well tested

  auto test_helper {[&results](const std::list<ship::part> test_list,
                               const auto& valid_part_list,
                               const int severity_min,
                               const int severity_max,
                               std::string faction_name) {
    std::vector<int> tmp_vec;

    for ( const auto& p : test_list ) {
      results.add_case(ehanc::contains(valid_part_list.cbegin(),
                                       valid_part_list.cend(), p.id),
                       true, "Invalid Part ID - " + faction_name);
      results.add_case(p.damage >= severity_min
                           && p.damage <= severity_max,
                       true, "Invalid damage value - " + faction_name);
    }

    std::transform(test_list.cbegin(), test_list.cend(),
                   std::back_inserter(tmp_vec),
                   [&](const ship::part val) { return val.id; });

    std::sort(tmp_vec.begin(), tmp_vec.end());

    results.add_case(std::adjacent_find(tmp_vec.cbegin(), tmp_vec.cend())
                         == tmp_vec.cend(),
                     true, "Part ID not all unique - " + faction_name);
  }};

  test_helper(human_list, conf::human_part_list, conf::human_severity_min,
              conf::human_severity_max, "human");

  test_helper(ferengi_list, conf::ferengi_part_list,
              conf::ferengi_severity_min, conf::ferengi_severity_max,
              "ferengi");

  test_helper(klingon_list, conf::klingon_part_list,
              conf::klingon_severity_min, conf::klingon_severity_max,
              "klingon");

  test_helper(romulan_list, conf::romulan_part_list,
              conf::romulan_severity_min, conf::romulan_severity_max,
              "romulan");

  test_helper(other_list, conf::other_part_list, conf::other_severity_min,
              conf::other_severity_max, "other");

  return results;
}

auto test_construct_random_ship() -> ehanc::test
{
  ehanc::test results;

  // get_random_faction() and create_damaged_part_list already
  // tested

  return results;
}

void test_ship()
{
  ehanc::run_test("ship::create_damaged_part_list",
                  &test_create_damaged_part_list);
}
