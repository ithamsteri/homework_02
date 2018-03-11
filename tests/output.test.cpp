//
// File: output.test.cpp
//

#define BOOST_TEST_MODULE OutputTest
#include <boost/test/unit_test.hpp>

#include "output.h"
#include "types.h"
#include <sstream>

BOOST_AUTO_TEST_CASE(test_output) {
  std::string result{"77.73.142.211"};
  std::ostringstream stream;

  stream << address_type{77, 73, 142, 211};

  BOOST_CHECK_EQUAL(stream.str(), result);
}
