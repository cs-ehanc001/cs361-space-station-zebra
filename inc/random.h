#ifndef RANDOM_H
#define RANDOM_H

#include <random>

/* {{{ doc */
/**
 * @brief Returns a random engine. Exists to avoid constructing multiple
 * random engines.
 */
/* }}} */
auto random_engine() noexcept -> std::mt19937&;

#endif
