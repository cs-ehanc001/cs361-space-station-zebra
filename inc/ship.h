#ifndef SHIP_H
#define SHIP_H

#include "constants.h"
#include "list.hpp"

namespace zebra {

class ship
{
private:

  struct part {
    int id;
    int damage;
  };

  int m_id;

  ehanc::list<part> m_parts;

public:

  ship() noexcept;

  ship(const ship& src) noexcept;

  auto operator=(const ship& rhs) -> ship& noexcept;

  ship(ship&& src) noexcept;

  auto operator=(ship&& rhs) -> ship& noexcept;

  virtual ~ship() noexcept = default;
};

} // namespace zebra

#endif
