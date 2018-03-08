//
// File: filter.test.cpp
//

#define BOOST_TEST_MODULE Filter

#include "filter.h"
#include "io.h"
#include "ipaddr.h"
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <fstream>

using pool_type = std::vector<IPAddr>;

struct FilterFixture {
  pool_type testData;

  FilterFixture() {
    std::ifstream testFile("testdata.tsv");
    if (testFile.is_open()) {
      testData = readData(testFile);
      std::sort(testData.rbegin(), testData.rend());
    } else
      BOOST_FAIL("File with Test Data not found");
  }
};

void compareTwoPools(const pool_type &test, const pool_type &result) {
  BOOST_CHECK_EQUAL(test.size(), result.size());
  for (auto i = pool_type::size_type{0}; i < result.size(); i++) {
    if (test[i] != result[i])
      BOOST_FAIL("Not equal: " + test[i].str() + " and " + result[i].str());
  }
}

BOOST_FIXTURE_TEST_SUITE(FilterCheck, FilterFixture)

BOOST_AUTO_TEST_CASE(test_filter_1_arg) {
  pool_type result = {IPAddr("217.174.230.98"), IPAddr("217.82.152.217"),
                      IPAddr("217.25.18.126")};

  BOOST_TEST_MESSAGE("Checking filter by one argument");

  auto test = filter(testData, 217);
  compareTwoPools(test, result);
}

BOOST_AUTO_TEST_CASE(test_filter_2_arg) {
  pool_type result = {IPAddr("5.62.159.232"), IPAddr("5.62.154.52")};

  BOOST_TEST_MESSAGE("Checking filter by two argument");

  auto test = filter(testData, 5, 62);
  compareTwoPools(test, result);
}

BOOST_AUTO_TEST_CASE(test_filter_3_arg) {
  pool_type result = {IPAddr("182.75.81.122"), IPAddr("182.75.81.122"),
                      IPAddr("182.75.81.122"), IPAddr("182.75.81.108")};

  BOOST_TEST_MESSAGE("Checking filter by three argument");

  auto test = filter(testData, 182, 75, 81);
  compareTwoPools(test, result);
}

BOOST_AUTO_TEST_CASE(test_filter_4_arg) {
  pool_type result = {IPAddr("32.215.162.52"), IPAddr("32.215.162.52"),
                      IPAddr("32.215.162.52")};

  BOOST_TEST_MESSAGE("Checking filter by four argument");

  auto test = filter(testData, 32, 215, 162, 52);
  compareTwoPools(test, result);
}

BOOST_AUTO_TEST_CASE(test_filter_any_nofound) {
  BOOST_TEST_MESSAGE("Checking filter any without results");

  auto test = filter_any(testData, 46);
  compareTwoPools(test, pool_type{});
}

BOOST_AUTO_TEST_CASE(test_filter_any) {
  pool_type result = {IPAddr("217.82.152.217"), IPAddr("61.74.152.228"),
                      IPAddr("61.74.152.227")};

  BOOST_TEST_MESSAGE("Checking filter_any");

  auto test = filter_any(testData, 152);
  compareTwoPools(test, result);
}

BOOST_AUTO_TEST_CASE(test_filter_custom) {
  pool_type result = {IPAddr("61.74.152.228"), IPAddr("61.74.152.227"),
                      IPAddr("5.62.159.232"), IPAddr("1.87.203.225")};

  BOOST_TEST_MESSAGE("Checking filter_custom search ascending");

  // Address Search Ascending
  auto test = filter_custom(testData, [](const IPAddr &addr) {
    for (auto i = IPAddr::container_type::size_type{1}; i < addr.size(); i++)
      if (addr[i] < addr[i - 1])
        return false;
    return true;
  });
  compareTwoPools(test, result);
}

BOOST_AUTO_TEST_SUITE_END()
