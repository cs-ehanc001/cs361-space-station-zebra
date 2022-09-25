#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>
#include <string_view>

namespace conf {

using random_engine = std::mt19937;

/**
 * @brief Number of time steps to perform by default.
 * Can be overwritten by the command-line option `--steps`.
 *
 * @note Submitting: `10'000`
 */
constexpr inline int default_time_steps {10'000};

/**
 * @brief Path to log file to use by default.
 * Can be overwritten by the command-line option `--logfile`.
 *
 * @note Submitting: `"zebra_diary.txt"`
 */
constexpr inline std::string_view default_log_file {"zebra_diary.txt"};

/**
 * @brief Determines if output will sent to stdout by default.
 * `true` will make available the command-line option `--quiet`
 * to suppress the output.
 * `false` will  make available the command-line option `--print`
 * to enable the output.
 *
 * @note Submitting: `true`
 */
constexpr inline bool print_to_console_by_default {true};

/**
 * @brief Determines if output will sent to a log file by default.
 * `true` will make available the command-line option `--no-log`
 * to suppress the output.
 * `false` will  make available the command-line option `--log`
 * to enable the output.
 *
 * @note Submitting: `true`
 */
constexpr inline bool write_to_logfile_by_default {true};

/**
 * @brief Number of repair bays that Space Station Zebra will
 * have.
 *
 * @note Submitting: `3`
 */
constexpr inline int num_repair_bays {3};

/**
 * @brief Maximum number of ships in the repair queue before
 * program exits.
 * This exists to avoid utilizing too much memory.
 *
 * @note Submitting: `5'000'000`
 */
constexpr inline std::size_t cutoff_queue_size {5'000'000};

/**
 * @brief Separator to be used for the header of each hour's log.
 *
 * @note Submitting:
 *   `"############################################################"`
 *
 */
constexpr inline std::string_view header_line {
    "############################################################"};

/**
 * @brief ID of the first ship to be generated.
 * ID numbers go up sequentially for each ship.
 *
 * @note Submitting: `100`
 */
constexpr inline int starting_ship_id {100};

/**
 * @brief Mean number of ships to be generated each time step.
 * Value is used in a poisson mean distribution, which only
 * allows values >= 0.
 *
 * @note Submitting: `1.2`
 */
constexpr inline double new_ship_count_poisson_mean {1.2};

/**
 * @brief Chance of a human ship being generated, as a percentage.
 *
 * @note Submitting: `50`
 *
 * @warning human_ship_chance + ferengi_ship_chance + klingon_ship_chance
 * + romulan_ship_chance + other_ship_chance MUST be equal to 100.
 * Compilation will fail otherwise, checked by a `static_assert`.
 */
constexpr inline int human_ship_chance {50};

/**
 * @brief Chance of a human ship being generated, as a percentage.
 *
 * @note Submitting: `15`
 *
 * @warning human_ship_chance + ferengi_ship_chance + klingon_ship_chance
 * + romulan_ship_chance + other_ship_chance MUST be equal to 100.
 * Compilation will fail otherwise, checked by a `static_assert`.
 */
constexpr inline int ferengi_ship_chance {15};

/**
 * @brief Chance of a human ship being generated, as a percentage.
 *
 * @note Submitting: `10`
 *
 * @warning human_ship_chance + ferengi_ship_chance + klingon_ship_chance
 * + romulan_ship_chance + other_ship_chance MUST be equal to 100.
 * Compilation will fail otherwise, checked by a `static_assert`.
 */
constexpr inline int klingon_ship_chance {10};

/**
 * @brief Chance of a human ship being generated, as a percentage.
 *
 * @note Submitting: `5`
 *
 * @warning human_ship_chance + ferengi_ship_chance + klingon_ship_chance
 * + romulan_ship_chance + other_ship_chance MUST be equal to 100.
 * Compilation will fail otherwise, checked by a `static_assert`.
 */
constexpr inline int romulan_ship_chance {5};

/**
 * @brief Chance of a human ship being generated, as a percentage.
 *
 * @note Submitting: `20`
 *
 * @warning human_ship_chance + ferengi_ship_chance + klingon_ship_chance
 * + romulan_ship_chance + other_ship_chance MUST be equal to 100.
 * Compilation will fail otherwise, checked by a `static_assert`.
 */
constexpr inline int other_ship_chance {20};

// Ensure ship chances are set to valid values
static_assert(human_ship_chance + ferengi_ship_chance + klingon_ship_chance
                      + romulan_ship_chance + other_ship_chance
                  == 100,
              "Sum of ship type chances != 100%");

/**
 * @brief Minimum severity of damage to a human ship part.
 * Range is inclusive.
 *
 * @note Submitting: `1`
 */
constexpr inline int human_severity_min {1};

/**
 * @brief Maximum severity of damage to a human ship part.
 * Range is inclusive.
 *
 * @note Submitting: `5`
 */
constexpr inline int human_severity_max {5};

/**
 * @brief Minimum severity of damage to a ferengi ship part.
 * Range is inclusive.
 *
 * @note Submitting: `2`
 */
constexpr inline int ferengi_severity_min {2};

/**
 * @brief Maximum severity of damage to a ferengi ship part.
 * Range is inclusive.
 *
 * @note Submitting: `7`
 */
constexpr inline int ferengi_severity_max {7};

/**
 * @brief Minimum severity of damage to a klingon ship part.
 * Range is inclusive.
 *
 * @note Submitting: `2`
 */
constexpr inline int klingon_severity_min {2};

/**
 * @brief Maximum severity of damage to a klingon ship part.
 * Range is inclusive.
 *
 * @note Submitting: `6`
 */
constexpr inline int klingon_severity_max {6};

/**
 * @brief Minimum severity of damage to a romulan ship part.
 * Range is inclusive.
 *
 * @note Submitting: `3`
 */
constexpr inline int romulan_severity_min {3};

/**
 * @brief Maximum severity of damage to a romulan ship part.
 * Range is inclusive.
 *
 * @note Submitting: `7`
 */
constexpr inline int romulan_severity_max {7};

/**
 * @brief Minimum severity of damage to an other ship part.
 * Range is inclusive.
 *
 * @note Submitting: `1`
 */
constexpr inline int other_severity_min {1};

/**
 * @brief Maximum severity of damage to an other ship part.
 * Range is inclusive.
 *
 * @note Submitting: `10`
 */
constexpr inline int other_severity_max {10};

/**
 * @brief Mean number of broken parts a ship has when generated.
 * Mean is fed into a normal distribution.
 *
 * @note Submitting: `7.0`
 */
constexpr inline double broken_part_count_mean {7.0};

/**
 * @brief Standard deviation of distribution of number of broken parts a
 * ship has when generated.
 * Standard deviation is fed into a normal distribution.
 *
 * @note Submitting: `3.0`
 */
constexpr inline double broken_part_count_stddev {3.0};

/**
 * @brief Minimum number of broken parts a ship can have when generated.
 * If random number generation produces a value less than this,
 * that value will be discarded and this value will be used.
 *
 * @note Submitting: `1`
 */
constexpr inline int broken_part_count_min {1};

/**
 * @brief Function which converts severity of damage
 * (`damage` member of `ship::part`) to time remaining.
 *
 * @note Submitting: `return std::max(severity / 5, 1);`
 *
 * @warning Must not return 0!
 */
constexpr auto severity_to_time(int severity) noexcept -> int
{
  // returning 0 causes problems
  return std::max(severity / 5, 1);
}

/**
 * @brief List of valid part IDs for parts in a human ship.
 */
constexpr std::array<int, 100> human_part_list {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
    35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
    69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
    86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};

/**
 * @brief List of valid part IDs for parts in a ferengi ship.
 */
constexpr std::array<int, 76> ferengi_part_list {
    75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
    88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100,
    101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
    114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126,
    127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
    140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150};

/**
 * @brief List of valid part IDs for parts in a klingon ship.
 */
constexpr std::array<int, 100> klingon_part_list {
    2,   4,   6,   8,   10,  12,  14,  16,  18,  20,  22,  24,  26,
    28,  30,  32,  34,  36,  38,  40,  42,  44,  46,  48,  50,  52,
    54,  56,  58,  60,  62,  64,  66,  68,  70,  72,  74,  76,  78,
    80,  82,  84,  86,  88,  90,  92,  94,  96,  98,  100, 102, 104,
    106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130,
    132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156,
    158, 160, 162, 164, 166, 168, 170, 172, 174, 176, 178, 180, 182,
    184, 186, 188, 190, 192, 194, 196, 198, 200};

/**
 * @brief List of valid part IDs for parts in a romulan ship.
 */
constexpr std::array<int, 100> romulan_part_list {
    1,   3,   5,   7,   9,   11,  13,  15,  17,  19,  21,  23,  25,
    27,  29,  31,  33,  35,  37,  39,  41,  43,  45,  47,  49,  51,
    53,  55,  57,  59,  61,  63,  65,  67,  69,  71,  73,  75,  77,
    79,  81,  83,  85,  87,  89,  91,  93,  95,  97,  99,  101, 103,
    105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 129,
    131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155,
    157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181,
    183, 185, 187, 189, 191, 193, 195, 197, 199};

/**
 * @brief List of valid part IDs for parts in an other ship.
 */
constexpr std::array<int, 800> other_part_list {
    200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213,
    214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227,
    228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241,
    242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
    256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269,
    270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283,
    284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297,
    298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311,
    312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325,
    326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339,
    340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353,
    354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367,
    368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381,
    382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395,
    396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409,
    410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423,
    424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437,
    438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451,
    452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465,
    466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479,
    480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493,
    494, 495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507,
    508, 509, 510, 511, 512, 513, 514, 515, 516, 517, 518, 519, 520, 521,
    522, 523, 524, 525, 526, 527, 528, 529, 530, 531, 532, 533, 534, 535,
    536, 537, 538, 539, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549,
    550, 551, 552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563,
    564, 565, 566, 567, 568, 569, 570, 571, 572, 573, 574, 575, 576, 577,
    578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591,
    592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602, 603, 604, 605,
    606, 607, 608, 609, 610, 611, 612, 613, 614, 615, 616, 617, 618, 619,
    620, 621, 622, 623, 624, 625, 626, 627, 628, 629, 630, 631, 632, 633,
    634, 635, 636, 637, 638, 639, 640, 641, 642, 643, 644, 645, 646, 647,
    648, 649, 650, 651, 652, 653, 654, 655, 656, 657, 658, 659, 660, 661,
    662, 663, 664, 665, 666, 667, 668, 669, 670, 671, 672, 673, 674, 675,
    676, 677, 678, 679, 680, 681, 682, 683, 684, 685, 686, 687, 688, 689,
    690, 691, 692, 693, 694, 695, 696, 697, 698, 699, 700, 701, 702, 703,
    704, 705, 706, 707, 708, 709, 710, 711, 712, 713, 714, 715, 716, 717,
    718, 719, 720, 721, 722, 723, 724, 725, 726, 727, 728, 729, 730, 731,
    732, 733, 734, 735, 736, 737, 738, 739, 740, 741, 742, 743, 744, 745,
    746, 747, 748, 749, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759,
    760, 761, 762, 763, 764, 765, 766, 767, 768, 769, 770, 771, 772, 773,
    774, 775, 776, 777, 778, 779, 780, 781, 782, 783, 784, 785, 786, 787,
    788, 789, 790, 791, 792, 793, 794, 795, 796, 797, 798, 799, 800, 801,
    802, 803, 804, 805, 806, 807, 808, 809, 810, 811, 812, 813, 814, 815,
    816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829,
    830, 831, 832, 833, 834, 835, 836, 837, 838, 839, 840, 841, 842, 843,
    844, 845, 846, 847, 848, 849, 850, 851, 852, 853, 854, 855, 856, 857,
    858, 859, 860, 861, 862, 863, 864, 865, 866, 867, 868, 869, 870, 871,
    872, 873, 874, 875, 876, 877, 878, 879, 880, 881, 882, 883, 884, 885,
    886, 887, 888, 889, 890, 891, 892, 893, 894, 895, 896, 897, 898, 899,
    900, 901, 902, 903, 904, 905, 906, 907, 908, 909, 910, 911, 912, 913,
    914, 915, 916, 917, 918, 919, 920, 921, 922, 923, 924, 925, 926, 927,
    928, 929, 930, 931, 932, 933, 934, 935, 936, 937, 938, 939, 940, 941,
    942, 943, 944, 945, 946, 947, 948, 949, 950, 951, 952, 953, 954, 955,
    956, 957, 958, 959, 960, 961, 962, 963, 964, 965, 966, 967, 968, 969,
    970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 980, 981, 982, 983,
    984, 985, 986, 987, 988, 989, 990, 991, 992, 993, 994, 995, 996, 997,
    998, 999};

} // namespace conf

#endif
