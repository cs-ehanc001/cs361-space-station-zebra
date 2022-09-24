#include <algorithm>
#include <numeric>
#include <vector>

#include "utils/algorithm.hpp"
#include "utils/etc.hpp"

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

// also tests ship(faction), is_damaged(), repair(),
// get_damaged_part_count(), and get_id() incidentally
auto test_construct_random_ship() -> ehanc::test
{
  ehanc::test results;

  const int sample_size {5000};

  std::vector<ship> samples;
  samples.reserve(sample_size);
  for ( int i {0}; i < sample_size; ++i ) {
    samples.push_back(ship::construct_random_ship());
  }

  int ref {conf::starting_ship_id - 1};

  using namespace ehanc::literals::size_t_literal;
  std::for_each(samples.begin(), samples.end(), [&](ship& sample) {
    results.add_case(sample.get_id(), ++ref, "Bad ID");
    results.add_case(sample.is_damaged(), true, "Not damaged");
    int total_damage {sample.get_total_damage()};
    results.add_case(total_damage > 0, true,
                     "Bad total damage value: "
                         + std::to_string(total_damage));
    std::size_t damaged_part_count {sample.get_damaged_part_count()};
    results.add_case(damaged_part_count > 0_z, true,
                     "Bad damaged part cout: "
                         + std::to_string(damaged_part_count));
    /*******************************************************************/
    sample.repair();
    /*******************************************************************/
    results.add_case(sample.is_damaged(), false, "Damaged after repair");
    total_damage = sample.get_total_damage();
    results.add_case(total_damage == 0, true,
                     "Bad total damage value after repair: "
                         + std::to_string(total_damage));
    damaged_part_count = sample.get_damaged_part_count();
    results.add_case(damaged_part_count == 0, true,
                     "Bad damaged part cout after repair: "
                         + std::to_string(damaged_part_count));
  });

  return results;
}

auto test_get_total_damage() -> ehanc::test
{
  ehanc::test results;

  const int sample_size {5000};

  const std::vector<ship> samples {[sample_size]() -> std::vector<ship> {
    std::vector<ship> retval;
    retval.reserve(sample_size);
    for ( int i {0}; i < sample_size; ++i ) {
      retval.push_back(ship::construct_random_ship());
    }
    return retval;
  }()}; // IILE

  std::for_each(samples.cbegin(), samples.cend(), [&](const ship& sample) {
    const std::list<ship::part>& damaged_part_list {
        sample.get_damaged_parts_list()};
    const int actual_damage {[&]() -> int {
      std::vector<int> tmp_vec;
      tmp_vec.reserve(sample_size);
      std::transform(damaged_part_list.cbegin(), damaged_part_list.cend(),
                     std::back_inserter(tmp_vec),
                     [](const ship::part& val) { return val.damage; });
      return std::accumulate(tmp_vec.cbegin(), tmp_vec.cend(), 0);
    }()};
    results.add_case(sample.get_total_damage(), actual_damage,
                     "Wrong total damage");
  });

  return results;
}

void test_ship()
{
  ehanc::run_test("ship::create_damaged_part_list",
                  &test_create_damaged_part_list);
  ehanc::run_test("ship::construct_random_ship",
                  &test_construct_random_ship);
  ehanc::run_test("ship::get_total_damage", &test_get_total_damage);
}
