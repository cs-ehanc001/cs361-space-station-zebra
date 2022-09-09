#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "utils/metaprogramming.hpp"

namespace ehanc {

/* {{{ doc */
/**
 * @brief A re-implementation of std::list. If behavior deviates from
 * std::list in any way other than a missing member function, that is a
 * bug. Thus, cppreference should be adequate reference.
 */
/* }}} */
template <typename T>
class list
{
public:

  using value_type      = T;
  using size_type       = std::size_t;
  using reference       = T&;
  using const_reference = const T&;
  using pointer         = T*;
  using const_pointer   = const T*;

private:

  /* {{{ Node */
  struct Node {
    /* {{{ doc */
    /**
     * @brief The data contained in the node.
     */
    /* }}} */
    value_type m_data {};

    /* {{{ doc */
    /**
     * @brief Pointer to the next node in the list. If node is the tail,
     * this value is `nullptr`.
     */
    /* }}} */
    Node* m_next {};

    /* {{{ doc */
    /**
     * @brief Pointer to the previous node in the list. If node is the
     * head, this value is `nullptr`.
     */
    /* }}} */
    Node* m_prev {};

    Node()  = default;
    ~Node() = default;

    // No need for copy and move operations
    Node(const Node&)           = delete;
    auto operator=(const Node&) = delete;
    Node(Node&&)                = delete;
    auto operator=(Node&&)      = delete;

    /* {{{ doc */
    /**
     * @brief Construct a node with given data.
     *
     * @param data The data to be contained.
     */
    /* }}} */
    template <typename data_t>
    Node(data_t&& data)
        : m_data {std::forward<data_t>(data)}
    {}
  }; // struct Node

  /* }}} Node */

  /* {{{ Data members */
  Node* m_head {};
  Node* m_tail {};
  size_type m_size {};

  // Dataless nodes for iterator reasons
  Node* m_ends {}; // serves as both endpoints
                   /* }}} Data members */

public:

  /* {{{ Special member functions */

  /* {{{ doc */
  /**
   * @brief Default constructor defaulted.
   */
  /* }}} */
  list()
      : m_ends {new Node}
  {
    // tie together false nodes (not needed?)
    /* m_fend->m_prev = m_rend; */
    /* m_rend->m_next = m_fend; */

    // seems odd, but makes iteration over empty list not segfault
    m_head = m_ends;
    m_tail = m_ends;
  }

  explicit list(size_type count)
      : m_ends {new Node}
  {
    for ( size_type i {0}; i < count; ++i ) {
      this->emplace_back();
    }
  }

  explicit list(size_type count, const_reference value)
      : m_ends {new Node}
  {
    for ( size_type i {0}; i < count; ++i ) {
      this->push_back(value);
    }
  }

  template <typename Iter>
  explicit list(Iter begin,
                std::enable_if_t<ehanc::is_iterator_v<Iter>, Iter> end)
      : m_ends {new Node}
  {
    std::copy(begin, end, std::back_inserter(*this));
  }

  list(std::initializer_list<value_type> init)
      : m_ends {new Node}
  {
    std::copy(init.begin(), init.end(), std::back_inserter(*this));
  }

  /* {{{ doc */
  /**
   * @brief Destructor removes all list elements.
   */
  /* }}} */
  ~list()
  {
    this->clear();
    delete m_ends;
  }

  /* {{{ doc */
  /**
   * @brief Copy constructor.
   */
  /* }}} */
  list(const list& src)
      : m_ends {new Node}
  {
    for ( const_reference element : src ) {
      this->push_back(element);
    }
  }

  /* {{{ doc */
  /**
   * @brief Copy assignment.
   */
  /* }}} */
  auto operator=(const list& rhs) -> list&
  {
    // handle self-assignment
    if ( this == &rhs ) {
      return *this;
    }

    this->clear();

    for ( const_reference element : rhs ) {
      this->push_back(element);
    }

    return *this;
  }

  /* {{{ doc */
  /**
   * @brief Move constructor.
   */
  /* }}} */
  list(list&& src) noexcept
      : m_head {src.m_head}
      , m_tail {src.m_tail}
      , m_size {src.m_size}
      , m_ends {src.m_ends}
  {
    src.m_head = nullptr;
    src.m_tail = nullptr;
    src.m_size = 0;
    src.m_ends = nullptr;
  }

  /* {{{ doc */
  /**
   * @brief Move assignment.
   */
  /* }}} */
  auto operator=(list&& rhs) noexcept -> list&
  {
    // handle self-assignment
    if ( this == &rhs ) {
      return *this;
    }

    this->clear();
    delete m_ends;

    m_head = rhs.m_head;
    m_tail = rhs.m_tail;
    m_size = rhs.m_size;
    m_ends = rhs.m_ends;

    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    rhs.m_size = 0;
    rhs.m_ends = nullptr;

    return *this;
  }

  /* }}} Special member functions */

  /* {{{ Member Functions */
  void assign(size_type count, const_reference value)
  {
    this->clear();

    for ( size_type i {0}; i < count; ++i ) {
      this->push_back(value);
    }
  }

  template <typename Iter>
  auto assign(Iter begin, Iter end)
      -> std::enable_if_t<ehanc::is_iterator_v<Iter>, void>
  {
    this->clear();
    std::copy(begin, end, std::back_inserter(*this));
  }

  void assign(std::initializer_list<value_type> ilist)
  {
    this->clear();
    std::copy(ilist.begin(), ilist.end(), std::back_inserter(*this));
  }

  /* }}} Member Functions */

  /* {{{ Iterators */

private:

  /* {{{ Iterator_Base */
  template <bool is_const>
  class Iterator_Base
  {
  public:

    using value_type        = std::conditional_t<is_const, const T, T>;
    using difference_type   = std::ptrdiff_t;
    using pointer           = std::conditional_t<is_const, const T*, T*>;
    using reference         = std::conditional_t<is_const, const T&, T&>;
    using iterator_category = std::bidirectional_iterator_tag;

    friend class ::ehanc::list<T>;

  private:

    Node* m_node {};

  public:

    Iterator_Base() = default;

    Iterator_Base(Node* ptr)
        : m_node {ptr}
    {}

    ~Iterator_Base()                                           = default;
    Iterator_Base(const Iterator_Base&)                        = default;
    auto operator=(const Iterator_Base&) -> Iterator_Base&     = default;
    Iterator_Base(Iterator_Base&&) noexcept                    = default;
    auto operator=(Iterator_Base&&) noexcept -> Iterator_Base& = default;

    [[nodiscard]] auto operator*() -> reference
    {
      return m_node->m_data;
    }

    auto operator++() -> Iterator_Base&
    {
      m_node = m_node->m_next;
      return *this;
    }

    auto operator++(int) -> Iterator_Base
    {
      Iterator_Base tmp {*this};
      this->operator++();
      return tmp;
    }

    auto operator--() -> Iterator_Base&
    {
      m_node = m_node->m_prev;
      return *this;
    }

    auto operator--(int) -> Iterator_Base
    {
      Iterator_Base tmp {*this};
      this->operator--();
      return tmp;
    }

    [[nodiscard]] auto operator==(const Iterator_Base& rhs) -> bool
    {
      return m_node == rhs.m_node;
    }

    [[nodiscard]] auto operator!=(const Iterator_Base& rhs) -> bool
    {
      return m_node != rhs.m_node;
    }

    operator Iterator_Base<true>()
    {
      return Iterator_Base<true>(this->m_node);
    }

  }; // class Iterator_Base

  /* }}} Iterator_Base */

  /* {{{ Reverse_Iterator_Base */
  template <bool is_const>
  class Reverse_Iterator_Base
  {
  public:

    using value_type        = std::conditional_t<is_const, const T, T>;
    using difference_type   = std::ptrdiff_t;
    using pointer           = std::conditional_t<is_const, const T*, T*>;
    using reference         = std::conditional_t<is_const, const T&, T&>;
    using iterator_category = std::bidirectional_iterator_tag;

  private:

    Node* m_node {};

  public:

    Reverse_Iterator_Base() = default;

    Reverse_Iterator_Base(Node* ptr)
        : m_node {ptr}
    {}

    ~Reverse_Iterator_Base()                            = default;
    Reverse_Iterator_Base(const Reverse_Iterator_Base&) = default;
    auto operator=(const Reverse_Iterator_Base&)
        -> Reverse_Iterator_Base&                           = default;
    Reverse_Iterator_Base(Reverse_Iterator_Base&&) noexcept = default;
    auto operator=(Reverse_Iterator_Base&&) noexcept
        -> Reverse_Iterator_Base& = default;

    [[nodiscard]] auto operator*() -> reference
    {
      return m_node->m_data;
    }

    auto operator++() -> Reverse_Iterator_Base&
    {
      m_node = m_node->m_prev;
      return *this;
    }

    auto operator++(int) -> Reverse_Iterator_Base
    {
      Reverse_Iterator_Base tmp {*this};
      this->operator++();
      return tmp;
    }

    auto operator--() -> Reverse_Iterator_Base&
    {
      m_node = m_node->m_next;
      return *this;
    }

    auto operator--(int) -> Reverse_Iterator_Base
    {
      Reverse_Iterator_Base tmp {*this};
      this->operator--();
      return tmp;
    }

    [[nodiscard]] auto operator==(const Reverse_Iterator_Base& rhs) -> bool
    {
      return m_node == rhs.m_node;
    }

    [[nodiscard]] auto operator!=(const Reverse_Iterator_Base& rhs) -> bool
    {
      return m_node != rhs.m_node;
    }

    operator Reverse_Iterator_Base<true>()
    {
      return Reverse_Iterator_Base<true>(this->m_node);
    }

  }; // class Reverse_Iterator_Base

  /* }}} Reverse_Iterator_Base */

public:

  using iterator               = Iterator_Base<false>;
  using const_iterator         = Iterator_Base<true>;
  using reverse_iterator       = Reverse_Iterator_Base<false>;
  using const_reverse_iterator = Reverse_Iterator_Base<true>;

  [[nodiscard]] auto begin() -> iterator
  {
    return iterator(m_head);
  }

  [[nodiscard]] auto begin() const -> const_iterator
  {
    return const_iterator(m_head);
  }

  [[nodiscard]] auto cbegin() const -> const_iterator
  {
    return const_iterator(m_head);
  }

  [[nodiscard]] auto end() -> iterator
  {
    return iterator(m_ends);
  }

  [[nodiscard]] auto end() const -> const_iterator
  {
    return const_iterator(m_ends);
  }

  [[nodiscard]] auto cend() const -> const_iterator
  {
    return const_iterator(m_ends);
  }

  [[nodiscard]] auto rbegin() -> reverse_iterator
  {
    return reverse_iterator(m_tail);
  }

  [[nodiscard]] auto rbegin() const -> const_reverse_iterator
  {
    return const_reverse_iterator(m_tail);
  }

  [[nodiscard]] auto crbegin() const -> const_reverse_iterator
  {
    return const_reverse_iterator(m_tail);
  }

  [[nodiscard]] auto rend() -> reverse_iterator
  {
    return reverse_iterator(m_ends);
  }

  [[nodiscard]] auto rend() const -> const_reverse_iterator
  {
    return const_reverse_iterator(m_ends);
  }

  [[nodiscard]] auto crend() const -> const_reverse_iterator
  {
    return const_reverse_iterator(m_ends);
  }

  /* }}} Iterators */

  /* {{{ Element Access */
  [[nodiscard]] auto front() -> reference
  {
    return m_head->m_data;
  }

  [[nodiscard]] auto front() const -> const_reference
  {
    return m_head->m_data;
  }

  [[nodiscard]] auto back() -> reference
  {
    return m_tail->m_data;
  }

  [[nodiscard]] auto back() const -> const_reference
  {
    return m_tail->m_data;
  }

  /* }}} Element Access */

  /* {{{ Modifiers */
  template <typename... Pack>
  auto emplace_back(Pack&&... pack) -> reference
  {
    Node* new_node {new Node(value_type(std::forward<Pack>(pack)...))};

    if ( this->empty() ) {
      m_ends->m_prev   = new_node;
      m_ends->m_next   = new_node;
      new_node->m_next = m_ends;
      new_node->m_prev = m_ends;
      m_head           = new_node;
      m_tail           = new_node;
    } else {
      m_tail->m_next   = new_node;
      m_ends->m_prev   = new_node;
      new_node->m_next = m_ends;
      new_node->m_prev = m_tail;
      m_tail           = new_node;
    }

    ++m_size;

    return m_tail->m_data;
  }

  template <typename data_t>
  void push_back(data_t&& data) noexcept
  {
    this->emplace_back(std::forward<data_t>(data));
  }

  template <typename... Pack>
  auto emplace_front(Pack&&... pack) -> reference
  {
    Node* new_node {new Node(value_type(std::forward<Pack>(pack)...))};

    if ( this->empty() ) {
      m_ends->m_prev   = new_node;
      m_ends->m_next   = new_node;
      new_node->m_next = m_ends;
      new_node->m_prev = m_ends;
      m_head           = new_node;
      m_tail           = new_node;
    } else {
      m_head->m_prev   = new_node;
      m_ends->m_next   = new_node;
      new_node->m_prev = m_ends;
      new_node->m_next = m_head;
      m_head           = new_node;
    }

    ++m_size;

    return m_head->m_data;
  }

  template <typename data_t>
  void push_front(data_t&& data) noexcept
  {
    this->emplace_front(std::forward<data_t>(data));
  }

  void pop_back()
  {
    if ( this->size() == 1 ) {
      assert(m_head == m_tail);
      m_ends->m_prev = m_ends;
      m_ends->m_next = m_ends;
      delete m_tail;
      m_head = m_ends;
      m_tail = m_ends;
    } else {
      assert(m_head != m_tail);
      Node* new_tail   = m_tail->m_prev;
      new_tail->m_next = m_ends;
      m_ends->m_prev   = new_tail;
      delete m_tail;
      m_tail = new_tail;
    }
    --m_size;
  }

  void pop_front()
  {
    if ( this->size() == 1 ) {
      assert(m_head == m_tail);
      m_ends->m_prev = m_ends;
      m_ends->m_next = m_ends;
      delete m_head;
      m_head = m_ends;
      m_tail = m_ends;
    } else {
      assert(m_head != m_tail);
      Node* new_head   = m_head->m_next;
      new_head->m_prev = m_ends;
      m_ends->m_next   = new_head;
      delete m_head;
      m_head = new_head;
    }
    --m_size;
  }

  void resize(size_type count)
  {
    if ( m_size > count ) {
      while ( m_size != count ) {
        this->pop_back();
      }
    } else if ( m_size < count ) {
      this->resize(count, value_type {});
    }
  }

  void resize(size_type count, const_reference value)
  {
    if ( m_size > count ) {
      while ( m_size != count ) {
        this->pop_back();
      }
    } else if ( m_size < count ) {
      this->emplace_back(value);
    }
  }

  auto erase(const_iterator pos) -> iterator
  {

    if ( pos == this->cbegin() ) {
      this->pop_front();
      return this->begin();

    } else if ( pos == std::prev(this->cend()) ) {
      this->pop_back();
      return this->end();

    } else if ( pos.m_node == m_ends ) {
      return this->end();

    } else {

      Node* erase_target {pos.m_node};
      Node* before {erase_target->m_prev};
      Node* after {erase_target->m_next};

      delete erase_target;
      before->m_next = after;
      after->m_prev  = before;
      --m_size;
      return after;
    }
  }

  auto erase(const_iterator begin, const_iterator end) -> iterator
  {
    if ( begin == end ) {
      return iterator(end.m_node);
    } else {
      while ( begin != end ) {
        auto erase_target {begin};
        ++begin;
        this->erase(erase_target);
      }
      return this->end();
    }
  }

  template <typename... Pack>
  auto emplace(const_iterator pos, Pack&&... pack) -> iterator
  {

    if ( pos == this->cbegin() ) {
      this->emplace_front(std::forward<Pack>(pack)...);
      return this->begin();
    } else if ( pos == this->cend() ) {
      this->emplace_back(std::forward<Pack>(pack)...);
      return std::prev(this->end());
    }

    Node* new_node {new Node(value_type(std::forward<Pack>(pack)...))};

    Node* insert_next {pos.m_node};
    Node* insert_prev {pos.m_node->m_prev};

    new_node->m_next    = insert_next;
    new_node->m_prev    = insert_prev;
    insert_next->m_prev = new_node;
    insert_prev->m_next = new_node;

    ++m_size;

    return iterator(new_node);
  }

  template <typename data_t>
  auto insert(const_iterator pos, data_t&& data) -> iterator
  {
    return this->emplace(pos, std::forward<data_t>(data));
  }

  auto insert(const_iterator pos, size_type count, const_reference data)
      -> iterator
  {
    Node* before_insert {pos.m_node->m_prev};

    for ( size_type i {0}; i != count; ++i ) {
      this->emplace(pos, data);
    }

    return iterator(before_insert->m_next);
  }

  template <typename Iter>
  auto insert(const_iterator pos, Iter begin, Iter end)
      -> std::enable_if_t<ehanc::is_iterator_v<Iter>, iterator>
  {
    Node* before_insert {pos.m_node->m_prev};
    while ( begin != end ) {
      this->emplace(pos, *begin);
      ++begin;
    }
    return iterator(before_insert->m_next);
  }

  auto insert(const_iterator pos, std::initializer_list<value_type> ilist)
  {
    auto begin {ilist.begin()};
    auto end {ilist.end()};

    Node* before_insert {pos.m_node->m_prev};
    while ( begin != end ) {
      this->emplace(pos, *begin);
      ++begin;
    }
    return iterator(before_insert->m_next);
  }

  void clear()

  {
    while ( !this->empty() ) {
      this->pop_back();
    }

    // seems odd, but makes iteration over empty list not segfault
    m_head = m_ends;
    m_tail = m_ends;
  }

  /* }}} Modifiers */

  /* {{{ Capacity */

  [[nodiscard]] auto size() const -> size_type
  {
    return m_size;
  }

  [[nodiscard]] auto empty() const -> bool
  {
    return m_size == 0;
  }

  /* }}} Capacity */

}; // class list

template <typename Iter>
list(Iter, Iter) -> list<typename std::iterator_traits<Iter>::value_type>;

} // namespace ehanc

#endif
