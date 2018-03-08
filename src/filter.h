//
// File: filter.h
//

#ifndef _FILTER_H_GUARD
#define _FILTER_H_GUARD

#include "ipaddr.h"
#include <functional>

using FilterPredicate = std::function<bool(const IPAddr &)>;

// Шаблонная функция, которая принимает контейнер с IP адресами,
// ищет заданные IP адреса и возвращает новый контейнер с найденными адресами.
// Работает с конейнерами у которых есть метод push_back():
//  - deque
//  - list
//  - vector
template <typename Container>
Container filter_custom(const Container &pool, FilterPredicate f) {
  Container result;

  for (const auto &addr : pool) {
    if (f(addr))
      result.push_back(addr);
  }

  return result;
}

template <typename Container>
Container filter(const Container &pool, int n0, int n1 = -1, int n2 = -1,
                 int n3 = -1) {
  return filter_custom(pool, [=](const IPAddr &addr) {
    return !(addr[0] != n0 || ((n1 > 0) && addr[1] != n1) ||
             ((n2 > 0) && addr[2] != n2) || ((n3 > 0) && addr[3] != n3));
  });
}

template <typename Container>
Container filter_any(const Container &pool, int n) {
  return filter_custom(pool, [=](const IPAddr &addr) {
    for (auto i = IPAddr::container_type::size_type{0}; i < addr.size(); i++) {
      if (addr[i] == n)
        return true;
    }
    return false;
  });
}

#endif // _FILTER_H_GUARD
