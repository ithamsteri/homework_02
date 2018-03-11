//
// File: main.cpp
//

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <vector>

using address_type = std::array<uint8_t, 4>;
using pool_type = std::vector<address_type>;

pool_type readData() {
  pool_type pool;

  for (std::string line; std::getline(std::cin, line);) {
    auto start = line.cbegin();
    address_type addr;
    
    for (auto i = address_type::size_type{0}; i < addr.size(); i++) {
      auto iter = start;
      while (iter != line.cend() && *iter != '.') iter++;
      
      auto value = std::stoi(std::string(start, iter++));
      addr[i] = static_cast<uint8_t>(value);
      start = iter;
    }
    
    pool.push_back(addr);
  }

  return pool;
}

std::ostream& operator<<(std::ostream& os, const address_type& addr)  
{
  for (auto iter = addr.cbegin(); iter != addr.cend(); iter++) {
    if (iter != addr.cbegin()) os << '.';
    os << static_cast<int>(*iter);
  }
  return os;  
}  

void filter(const pool_type& pool,
            int n0,      int n1 = -1,
            int n2 = -1, int n3 = -1) {
  for(const auto& addr : pool) {
    if (!(addr[0] != n0 ||
         ((n1 > 0) && addr[1] != n1) ||
         ((n2 > 0) && addr[2] != n2) ||
         ((n3 > 0) && addr[3] != n3)))
      std::cout << addr << std::endl;
  }
}

void filter_any(const pool_type& pool, int n) {
  for(const auto& addr : pool) {
    for (auto i = address_type::size_type{0}; i < addr.size(); i++)
      if (addr[i] == n) {
        std::cout << addr << std::endl;
        break;
      }
  }
}

int main(int, char* []) {
  pool_type pool = readData();

  std::sort(pool.rbegin(), pool.rend());

  for (const auto& addr : pool)
    std::cout << addr << std::endl;
  
  filter(pool, 1);
  filter(pool, 46, 70);
  filter_any(pool, 46);
}
