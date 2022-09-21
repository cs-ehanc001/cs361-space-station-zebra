#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

namespace conf {

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

constexpr std::array<int, 100> human_part_list {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
    35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
    69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
    86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};

constexpr std::array<int, 76> ferengi_part_list {
    75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
    88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100,
    101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
    114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126,
    127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
    140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150};

constexpr std::array<int, 100> klingon_part_list {
    2,   4,   6,   8,   10,  12,  14,  16,  18,  20,  22,  24,  26,
    28,  30,  32,  34,  36,  38,  40,  42,  44,  46,  48,  50,  52,
    54,  56,  58,  60,  62,  64,  66,  68,  70,  72,  74,  76,  78,
    80,  82,  84,  86,  88,  90,  92,  94,  96,  98,  100, 102, 104,
    106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130,
    132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156,
    158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182,
    184, 186, 188, 190, 192, 194, 196, 198, 200};

constexpr std::array<int, 100> romulan_part_list {
    1,   3,   5,   7,   9,   11,  13,  15,  17,  19,  21,  23,  25,
    27,  29,  31,  33,  35,  37,  39,  41,  43,  45,  47,  49,  51,
    53,  55,  57,  59,  61,  63,  65,  67,  69,  71,  73,  75,  77,
    79,  81,  83,  85,  87,  89,  91,  93,  95,  97,  99,  101, 103,
    105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 129,
    131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155,
    157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181,
    183, 185, 187, 189, 191, 193, 195, 197, 199};

} // namespace conf

#endif
