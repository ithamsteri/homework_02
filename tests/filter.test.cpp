#define BOOST_TEST_MODULE FilterTest
#include <boost/test/unit_test.hpp>

#include "filter.h"
#include "output.h"
#include <functional>
#include <iostream>
#include <sstream>

struct FilterFixture {
  pool_type testData;

  FilterFixture()
      : testData{
            {{77, 73, 142, 211}}, {{87, 250, 250, 242}}, {{80, 87, 192, 10}},
            {{46, 101, 99, 10}},  {{216, 18, 168, 16}},  {{49, 212, 130, 73}},
            {{80, 87, 192, 11}},  {{77, 71, 16, 173}},   {{10, 10, 10, 10}},
        } {
    std::sort(testData.rbegin(), testData.rend());
  }
};

// This function compare what print f() in std::cout with result string.
bool check_cout(const std::string &result, std::function<void()> f) {
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  bool r = false;

  f();
  if (buffer.str() == result)
    r = true;

  // restore std::cout buffer
  std::cout.rdbuf(old);

  return r;
}

BOOST_FIXTURE_TEST_SUITE(Filter, FilterFixture)

BOOST_AUTO_TEST_CASE(test_filter_01) {
  std::string result{"77.73.142.211\n77.71.16.173\n"};

  BOOST_CHECK(check_cout(result, [&]() { filter(testData, 77); }));
}

BOOST_AUTO_TEST_CASE(test_filter_02) {
  std::string result{"80.87.192.11\n80.87.192.10\n"};

  BOOST_CHECK(check_cout(result, [&]() { filter(testData, 80, 87); }));
}

BOOST_AUTO_TEST_CASE(test_filter_any) {
  std::string result{"80.87.192.10\n46.101.99.10\n10.10.10.10\n"};

  BOOST_CHECK(check_cout(result, [&]() { filter_any(testData, 10); }));
}

BOOST_AUTO_TEST_SUITE_END()
