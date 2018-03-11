//
// File: output.cpp
//

#include "output.h"

std::ostream &operator<<(std::ostream &os, const address_type &addr) {
  for (auto iter = addr.cbegin(); iter != addr.cend(); iter++) {
    if (iter != addr.cbegin())
      os << '.';
    os << static_cast<int>(*iter);
  }
  return os;
}
