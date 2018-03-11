//
// File: filter.cpp
//

#include "filter.h"
#include <iostream>

void filter(const pool_type &pool, int n0, int n1, int n2, int n3) {
  for (const auto &addr : pool) {
    if (!(addr[0] != n0 || ((n1 > 0) && addr[1] != n1) ||
          ((n2 > 0) && addr[2] != n2) || ((n3 > 0) && addr[3] != n3)))
      std::cout << addr << std::endl;
  }
}

void filter_any(const pool_type &pool, int n) {
  for (const auto &addr : pool) {
    for (auto i = address_type::size_type{0}; i < addr.size(); i++)
      if (addr[i] == n) {
        std::cout << addr << std::endl;
        break;
      }
  }
}
