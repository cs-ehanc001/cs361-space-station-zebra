#include <type_traits>

#include "test_queue.h"
#include "test_utils.hpp"

#include "utils/etc.hpp"

using ehanc::literals::size_t_literal::operator""_z;

auto test_copy_container_constructor() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(container);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

auto test_move_container_constructor() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(std::move(container));

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

auto test_iter_constructor() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(container.begin(), container.end());

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

auto test_front() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(container);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

auto test_back() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(container);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

auto test_empty() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(container);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

auto test_size() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(container);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

auto test_push() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(container);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);

  test.push(9);
  results.add_case(test.empty(), false);
  results.add_case(test.size(), 5_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 9);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 9);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 9);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 9);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 9);
  results.add_case(test.back(), 9);

  test.push(11);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 9);
  results.add_case(test.back(), 11);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 11);
  results.add_case(test.back(), 11);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

auto test_emplace() -> ehanc::test
{
  ehanc::test results;

  ehanc::list<std::pair<int, char>> container {
      {1, 'a'},
      {3, 'b'},
      {5, 'c'},
      {7, 'd'}
  };
  ehanc::queue<std::pair<int, char>> test(container);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), {1, 'a'});
  results.add_case(test.back(), {7, 'd'});

  decltype(auto) val1 {test.emplace(9, 'e')};
  results.add_case(val1, std::pair(9, 'e'));
  results.add_case(std::is_same_v<decltype(val1), std::pair<int, char>&>,
                   true);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 5_z);
  results.add_case(test.front(), {1, 'a'});
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), {3, 'b'});
  results.add_case(test.back(), {9, 'e'});
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), {5, 'c'});
  results.add_case(test.back(), {9, 'e'});
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), {7, 'd'});
  results.add_case(test.back(), {9, 'e'});
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), {9, 'e'});
  results.add_case(test.back(), {9, 'e'});

  decltype(auto) val2 {test.emplace(11, 'f')};
  results.add_case(val2, std::pair(11, 'f'));
  results.add_case(std::is_same_v<decltype(val2), std::pair<int, char>&>,
                   true);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), {9, 'e'});
  results.add_case(test.back(), {11, 'f'});
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), {11, 'f'});
  results.add_case(test.back(), {11, 'f'});
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  results.add_case(
      std::is_same_v<decltype(test.emplace(
                         std::declval<std::pair<int, char>>())),
                     std::pair<int, char>&>,
      true);

  return results;
}

auto test_pop() -> ehanc::test
{
  ehanc::test results;

  ehanc::list container {1, 3, 5, 7};
  ehanc::queue<int> test(container);

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 4_z);
  results.add_case(test.front(), 1);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 3_z);
  results.add_case(test.front(), 3);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 2_z);
  results.add_case(test.front(), 5);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), false);
  results.add_case(test.size(), 1_z);
  results.add_case(test.front(), 7);
  results.add_case(test.back(), 7);
  test.pop();

  results.add_case(test.empty(), true);
  results.add_case(test.size(), 0_z);

  return results;
}

void test_queue()
{
  ehanc::run_test("copy container constructor",
                  &test_copy_container_constructor);
  ehanc::run_test("move container constructor",
                  &test_move_container_constructor);
  ehanc::run_test("iter constructor", &test_iter_constructor);
  ehanc::run_test("front", &test_front);
  ehanc::run_test("back", &test_back);
  ehanc::run_test("empty", &test_empty);
  ehanc::run_test("size", &test_size);
  ehanc::run_test("push", &test_push);
  ehanc::run_test("emplace", &test_emplace);
  ehanc::run_test("pop", &test_pop);
}
