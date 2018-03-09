//
// File: filter.bench.cpp
//

#include "filter.h"
#include "io.h"
#include "ipaddr.h"
#include <benchmark/benchmark.h>
#include <fstream>
#include <stdexcept>
#include <vector>

using pool_type = std::vector<IPAddr>;

struct FilterFixture : public benchmark::Fixture {
  pool_type testData;

  FilterFixture() {
    std::ifstream testFile("benchdata.tsv");
    if (testFile.is_open()) {
      testData = readData(testFile);
      std::sort(testData.rbegin(), testData.rend());
    } else {
      throw std::runtime_error("File with test data not found!");
    }
  }
};

BENCHMARK_F(FilterFixture, FilterAnyBench)(benchmark::State &st) {
  for (auto _ : st) {
    filter_any(testData, 46);
  }
}

BENCHMARK_F(FilterFixture, FilterOneArg)(benchmark::State &st) {
  for (auto _ : st) {
    filter(testData, 11);
  }
}

BENCHMARK_F(FilterFixture, FilterTwoArg)(benchmark::State &st) {
  for (auto _ : st) {
    filter(testData, 12, 12);
  }
}

BENCHMARK_F(FilterFixture, FilterThreeArg)(benchmark::State &st) {
  for (auto _ : st) {
    filter(testData, 13, 13, 13);
  }
}

BENCHMARK_F(FilterFixture, FilterFourArg)(benchmark::State &st) {
  for (auto _ : st) {
    filter(testData, 14, 14, 14, 14);
  }
}

BENCHMARK_MAIN();
