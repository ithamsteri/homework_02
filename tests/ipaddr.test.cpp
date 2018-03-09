//
// File: ipaddr.test.cpp
//

#define BOOST_TEST_MODULE IPAddr

#include "ipaddr.h"
#include <array>
#include <boost/test/unit_test.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

using ippair = std::array<IPAddr, 2>;
using ipvec = std::array<int, 4>;

BOOST_AUTO_TEST_SUITE(ipaddr_test_basic)

BOOST_AUTO_TEST_CASE(not_correct_ip) {
  std::vector<std::string> addresses{
      "A.2.3.4",        "1.A.3.4",        "1.2.A.4",        "1.2.3.A",
      "10000000.2.3.4", "1.20000000.3.4", "1.2.30000000.4", "1.2.3.40000000",
      "666.2.3.4",      "1.666.3.4",      "1.2.666.4",      "1.2.3.666",
      "-1.2.3.4",       "1.-2.3.4",       "1.2.-3.4",       "1.2.3.-4"};

  // NOTE: https://stackoverflow.com/questions/2372027/
  // This occurs because BOOST_CHECK_THROW is a macro, and `IPAddr(address)`
  // is being expanded to a statement. The compiler sees this statement and
  // interprets it as a variable declaration `IPAddr address;` which requires
  // a default constructor.
  for (const auto &address : addresses) {
    BOOST_CHECK_THROW(auto _ = IPAddr(address), std::invalid_argument);
  }
}

BOOST_AUTO_TEST_CASE(access_test) {
  auto address = IPAddr("1.2.3.4");
  auto result = ipvec{1, 2, 3, 4};

  BOOST_TEST_MESSAGE("Checking IPAddr access over index");

  for (auto i = ipvec::size_type{0}; i < result.size(); i++)
    BOOST_CHECK_EQUAL(address[i], result[i]);
}

BOOST_AUTO_TEST_CASE(access_mutable_test) {
  auto address = IPAddr("1.2.3.4");
  auto result = ipvec{192, 168, 0, 255};

  BOOST_TEST_MESSAGE("Checking IPAddr change over index");

  // Change address
  for (auto i = ipvec::size_type{0}; i < result.size(); i++)
    address[i] = result[i];

  // Check address
  for (auto i = ipvec::size_type{0}; i < result.size(); i++)
    BOOST_CHECK_EQUAL(address[i], result[i]);
}

BOOST_AUTO_TEST_CASE(string_test) {
  std::vector<std::string> addresses{"0.0.0.0",   "255.255.255.255",
                                     "127.0.0.1", "10.10.10.10",
                                     "1.2.3.4",   "8.8.4.4"};

  BOOST_TEST_MESSAGE("Checking IPAddr string conversion");

  for (const auto &address : addresses) {
    auto ip = IPAddr(address);
    BOOST_CHECK_EQUAL(ip.str(), address);
  }
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ipaddr_test_compare)

BOOST_AUTO_TEST_CASE(compare_less_test) {
  std::map<ippair, bool> test = {
      std::make_pair(ippair{IPAddr("1.2.3.4"), IPAddr("1.2.3.5")}, true),
      std::make_pair(ippair{IPAddr("1.2.3.4"), IPAddr("1.2.3.40")}, true),
      std::make_pair(ippair{IPAddr("1.2.3.4"), IPAddr("1.2.3.3")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.0.0")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.0.1")}, true),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.1.0")}, true),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.1.0.0")}, true),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("1.0.0.0")}, true)};

  BOOST_TEST_MESSAGE("Checking IPAddr compare less");

  for (auto iter = test.begin(); iter != test.end(); ++iter)
    BOOST_CHECK_EQUAL(iter->first[0] < iter->first[1], iter->second);
}

BOOST_AUTO_TEST_CASE(compare_greater_test) {
  std::map<ippair, bool> test = {
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.0.0")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.0.1")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.1.0")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.1.0.0")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("1.0.0.0")}, false)};

  BOOST_TEST_MESSAGE("Checking IPAddr compare greater");

  for (auto iter = test.begin(); iter != test.end(); ++iter)
    BOOST_CHECK_EQUAL(iter->first[0] > iter->first[1], iter->second);
}

BOOST_AUTO_TEST_CASE(compare_less_or_equal_test) {
  std::map<ippair, bool> test = {
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.0.1")}, true),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.1.0")}, true),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.1.0.0")}, true),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("1.0.0.0")}, true),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.0.0")}, true)};

  BOOST_TEST_MESSAGE("Checking IPAddr compare less or equal");

  for (auto iter = test.begin(); iter != test.end(); ++iter)
    BOOST_CHECK_EQUAL(iter->first[0] <= iter->first[1], iter->second);
}

BOOST_AUTO_TEST_CASE(compare_greater_or_equal_test) {
  std::map<ippair, bool> test = {
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.0.1")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.1.0")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.1.0.0")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("1.0.0.0")}, false),
      std::make_pair(ippair{IPAddr("0.0.0.0"), IPAddr("0.0.0.0")}, true)};

  BOOST_TEST_MESSAGE("Checking IPAddr compare greater or equal");

  for (auto iter = test.begin(); iter != test.end(); ++iter)
    BOOST_CHECK_EQUAL(iter->first[0] >= iter->first[1], iter->second);
}

BOOST_AUTO_TEST_CASE(compare_equal_test) {
  std::map<ippair, bool> test = {
      std::make_pair(ippair{IPAddr("192.168.1.1"), IPAddr("192.168.1.1")},
                     true),
      std::make_pair(ippair{IPAddr("192.168.1.1"), IPAddr("192.168.1.10")},
                     false),
      std::make_pair(ippair{IPAddr("192.168.1.1"), IPAddr("192.168.10.1")},
                     false),
      std::make_pair(ippair{IPAddr("192.168.1.1"), IPAddr("19.168.1.1")},
                     false)};

  BOOST_TEST_MESSAGE("Checking IPAddr compare equal");

  for (auto iter = test.begin(); iter != test.end(); ++iter)
    BOOST_CHECK_EQUAL(iter->first[0] == iter->first[1], iter->second);
}

BOOST_AUTO_TEST_CASE(compare_not_equal_test) {
  std::map<ippair, bool> test = {
      std::make_pair(ippair{IPAddr("192.168.1.1"), IPAddr("192.168.1.1")},
                     false),
      std::make_pair(ippair{IPAddr("192.168.1.1"), IPAddr("192.168.1.10")},
                     true),
      std::make_pair(ippair{IPAddr("192.168.1.1"), IPAddr("192.168.10.1")},
                     true),
      std::make_pair(ippair{IPAddr("192.168.1.1"), IPAddr("19.168.1.1")},
                     true)};

  BOOST_TEST_MESSAGE("Checking IPAddr compare not equal");

  for (auto iter = test.begin(); iter != test.end(); ++iter)
    BOOST_CHECK_EQUAL(iter->first[0] != iter->first[1], iter->second);
}

BOOST_AUTO_TEST_SUITE_END()
