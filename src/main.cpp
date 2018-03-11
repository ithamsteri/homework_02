//
// File: main.cpp
//

#include "filter.h"
#include "output.h"
#include "types.h"
#include <algorithm>
#include <iostream>

pool_type readData() {
  pool_type pool;

  for (std::string line; std::getline(std::cin, line);) {
    auto start = line.cbegin();
    address_type addr;

    for (auto i = address_type::size_type{0}; i < addr.size(); i++) {
      auto iter = start;
      while (iter != line.cend() && *iter != '.')
        iter++;

      auto value = std::stoi(std::string(start, iter++));
      addr[i] = static_cast<uint8_t>(value);
      start = iter;
    }

    pool.push_back(addr);
  }

  return pool;
}

int main(int, char *[]) {
  pool_type pool = readData();

  std::sort(pool.rbegin(), pool.rend());

  for (const auto &addr : pool)
    std::cout << addr << std::endl;

  filter(pool, 1);
  filter(pool, 46, 70);
  filter_any(pool, 46);
}
