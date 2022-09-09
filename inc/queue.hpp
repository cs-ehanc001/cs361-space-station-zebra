#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <utility>

#include "list.hpp"

namespace ehanc {

/* {{{ doc */
/**
 * @brief Re-implementation of std::queue.
 *
 * @tparam T Value type of the queue.
 *
 * @tparam Container Type of container to use internally. Must provide
 * push_back, emplace_back, pop_front, front, back, empty, and size
 * member functions.
 */
/* }}} */
template <typename T, typename Container = ehanc::list<T>>
class queue
{
public:

  using container_type  = Container;
  using value_type      = T;
  using size_type       = container_type::size_type;
  using reference       = container_type::reference;
  using const_reference = container_type::const_reference;

private:

  container_type m_container;

public:

  queue() = default;

  queue(const queue& other) = default;

  auto operator=(const queue& rhs) -> queue& = default;

  queue(queue&& other) = default;

  auto operator=(queue&& rhs) -> queue& = default;

  ~queue() = default;

  explicit queue(const container_type& container)
      : m_container(container)
  {}

  explicit queue(container_type&& container)
      : m_container(std::move(container))
  {}

  template <typename Itr>
  queue(Itr begin, Itr end)
      : m_container(begin, end)
  {}

  [[nodiscard]] auto front() -> reference
  {
    return m_container.front();
  }

  [[nodiscard]] auto front() const -> const_reference
  {
    return m_container.front();
  }

  [[nodiscard]] auto back() -> reference
  {
    return m_container.back();
  }

  [[nodiscard]] auto back() const -> const_reference
  {
    return m_container.back();
  }

  [[nodiscard]] auto empty() const -> bool
  {
    return m_container.empty();
  }

  template <typename T>
  void push(T&& value)
  {
    m_container.push_back(std::forward(value));
  }

  template <typename... Pack>
  decltype(auto) emplace(Pack&&... pack)
  {
    m_container.emplace_back(std::forward<Pack>(pack)...);
  }

  void pop()
  {
    m_container.pop_front();
  }
};

} // namespace ehanc

#endif
