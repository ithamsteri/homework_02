//
// File: ipaddr.cpp
//

#include "ipaddr.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

const char *invalid_argument_error{"Not correct string with IP address."};

IPAddr::IPAddr(const std::string &addr) {
  auto start = addr.cbegin();
  for (auto i = container_type::size_type{0}; i < _addr.size(); i++) {
    auto iter = start;

    while (iter != addr.cend() && *iter != '.')
      iter++;

    try {
      int value = std::stoi(std::string(start, iter++));
      if ((value < 0) || (value > 255))
        throw std::invalid_argument(invalid_argument_error);

      _addr[i] = static_cast<internal_type>(value);
    } catch (const std::out_of_range &e) {
      // std::stoi can throw out_of_range,
      // if try parse number greater than int type
      throw std::invalid_argument(invalid_argument_error);
    }
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

bool IPAddr::operator==(const IPAddr &other) const {
  for (auto i = container_type::size_type{0}; i < _addr.size(); i++)
    if (_addr[i] != other._addr[i])
      return false;
  return true;
}
