//
// File: main.cpp
//

#include "filter.h"
#include "io.h"
#include "ipaddr.h"

int main(int, char *[]) {
  auto pool = readData(std::cin);
  std::sort(pool.rbegin(), pool.rend());
  print(std::cout, pool);

  auto result = filter(pool, 1);
  print(std::cout, result);

  result = filter(pool, 46, 70);
  print(std::cout, result);

  result = filter_any(pool, 46);
  print(std::cout, result);
}
