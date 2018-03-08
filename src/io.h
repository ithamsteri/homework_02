//
// File: io.h
//

#ifndef _IO_H_GUARD
#define _IO_H_GUARD

#include "ipaddr.h"
#include <algorithm>
#include <iostream>
#include <vector>

template <class Container = std::vector<IPAddr>>
Container readData(std::istream &istream) {
  Container pool;

  for (std::string line; std::getline(istream, line);) {
    pool.push_back(IPAddr(std::string(
        line.cbegin(), std::find(line.cbegin(), line.cend(), '\t'))));
  }

  return pool;
}

template <typename Container>
void print(std::ostream &ostream, const Container &pool) {
  for (const auto &addr : pool) {
    ostream << addr.str() << std::endl;
  }
}

#endif // _IO_H_GUARD
