#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr inline int num_repair_bays {3};

constexpr inline int starting_ship_id {100};

constexpr inline double new_ship_count_poisson_mean {1.2};

constexpr inline int human_ship_chance {50};
constexpr inline int ferengi_ship_chance {15};
constexpr inline int klingon_ship_chance {10};
constexpr inline int romulan_ship_chance {5};
constexpr inline int other_ship_chance {20};
static_assert(human_ship_chance + ferengi_ship_chance + klingon_ship_chance
                      + romulan_ship_chance + other_ship_chance
                  == 100,
              "Sum of ship type chances != 100%");

constexpr inline int human_bad_part_chance {5};
constexpr inline int ferengi_bad_part_chance {8};
constexpr inline int klingon_bad_part_chance {6};
constexpr inline int romulan_bad_part_chance {6};
constexpr inline int other_bad_part_chance {7};

constexpr inline int human_severity_min {1};
constexpr inline int human_severity_max {5};
constexpr inline int ferengi_severity_min {2};
constexpr inline int ferengi_severity_max {7};
constexpr inline int klingon_severity_min {2};
constexpr inline int klingon_severity_max {6};
constexpr inline int romulan_severity_min {3};
constexpr inline int romulan_severity_max {7};
constexpr inline int other_severity_min {1};
constexpr inline int other_severity_max {10};

constexpr auto severity_to_time(int severity) -> int
{
  return severity / 5;
}

#endif
