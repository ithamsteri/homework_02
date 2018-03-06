//
// File: ip_filter.test.cpp
//

#define BOOST_TEST_MODULE SimpleTest

#include "split.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Split)

BOOST_AUTO_TEST_CASE(splitCheckCase01) {
  std::vector<std::string> result1 = {""};
  BOOST_CHECK(split("", '.') == result1);
}

BOOST_AUTO_TEST_CASE(splitCheckCase02) {
  std::vector<std::string> result1 = {"11"};
  BOOST_CHECK(split("11", '.') == result1);
}

BOOST_AUTO_TEST_CASE(splitCheckCase03) {
  std::vector<std::string> result1 = {"", "", ""};
  BOOST_CHECK(split("..", '.') == result1);
}

BOOST_AUTO_TEST_CASE(splitCheckCase04) {
  std::vector<std::string> result1 = {"11", ""};
  BOOST_CHECK(split("11.", '.') == result1);
}

BOOST_AUTO_TEST_CASE(splitCheckCase05) {
  std::vector<std::string> result1 = {"", "11"};
  BOOST_CHECK(split(".11", '.') == result1);
}

BOOST_AUTO_TEST_CASE(splitCheckCase06) {
  std::vector<std::string> result1 = {"11", "22"};
  BOOST_CHECK(split("11.22", '.') == result1);
}

BOOST_AUTO_TEST_SUITE_END()
