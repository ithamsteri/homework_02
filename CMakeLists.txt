cmake_minimum_required(VERSION 3.2)

# check environment variable TRAVIS_BUILD_NUMBER
if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 0)
endif()

# This function automates this process by getting the current help string
# for the cache variable to update, then reinitialising it with the new
# value, but with the original help string.
function(update_cache_variable VAR_NAME VALUE)
  get_property(HELP_STRING CACHE ${VAR_NAME} PROPERTY HELPSTRING)
  get_property(VAR_TYPE CACHE ${VAR_NAME} PROPERTY TYPE)
  set(${VAR_NAME} ${VALUE} CACHE ${VAR_TYPE} "${HELP_STRING}" FORCE)
endfunction()

project(ipfilter VERSION 0.0.${VERSION_BUILD})

option(BUILD_BENCHMARKS "Build benchmarking suite" ON)

# configure directories
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

# we need boost for unit test
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# make executable file for application
add_executable(ip_filter
    ${SOURCE_PATH}/ip_filter.cpp
    ${SOURCE_PATH}/split.cpp
)
add_executable(split_test
    ${SOURCE_PATH}/split.test.cpp
    ${SOURCE_PATH}/split.cpp
)

set_target_properties(ip_filter split_test PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# BOOST_TEST_DYN_LINK - Define this flag to link against
# the Unit Test Framework shared library
set_target_properties(split_test PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(split_test
    ${Boost_LIBRARIES}
)

# If enabled option BUILD_BENCHMARKS:
if (BUILD_BENCHMARKS)
    find_package(benchmark QUIET)
    if (benchmark_FOUND)
        message("-- Found Google benchmark library. Building benchmarks.")
        add_executable(split_benchmark
            ${SOURCE_PATH}/split.bench.cpp
            ${SOURCE_PATH}/split.cpp
        )
        target_link_libraries(split_benchmark benchmark::benchmark)
    else()
        message("-- Failed to find Google benchmark library, disabling build of benchmarks.")
        update_cache_variable(BUILD_BENCHMARKS OFF)
    endif()
    mark_as_advanced(benchmark_DIR)
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT alex.aspirine@gmail.com)

include(CPack)

enable_testing()

add_test(split_test split_test)
