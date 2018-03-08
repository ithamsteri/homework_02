//
// File: ipaddr.cpp
//

#include "ipaddr.h"
#include <iostream>
#include <sstream>

IPAddr::IPAddr(const std::string &addr) {
  auto start = addr.cbegin();
  for (auto i = container_type::size_type{0}; i < _addr.size(); i++) {
    auto iter = start;

    while (iter != addr.cend() && *iter != '.')
      iter++;
    _addr[i] =
        static_cast<internal_type>(std::stoi(std::string(start, iter++)));

    start = iter;
  }
}

std::string IPAddr::str() const {
  std::ostringstream oss;

  for (auto iter = _addr.cbegin(); iter != _addr.cend(); iter++) {
    if (iter != _addr.cbegin())
      oss << '.';
    oss << static_cast<int>(*iter);
  }

  return oss.str();
}

bool IPAddr::operator<(const IPAddr &other) const {
  for (auto i = container_type::size_type{0}; i < _addr.size(); i++)
    if (_addr[i] != other._addr[i])
      return (_addr[i] < other._addr[i]) ? true : false;
  return false;
}

bool IPAddr::operator>(const IPAddr &other) const { return (*this < other); }

bool IPAddr::operator<=(const IPAddr &other) const { return !(*this > other); }

bool IPAddr::operator>=(const IPAddr &other) const { return !(*this < other); }

bool IPAddr::operator==(const IPAddr &other) const {
  for (auto i = container_type::size_type{0}; i < _addr.size(); i++)
    if (_addr[i] != other._addr[i])
      return false;
  return true;
}

bool IPAddr::operator!=(const IPAddr &other) const { return !(*this == other); }
