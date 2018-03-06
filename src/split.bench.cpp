//
// File: split.bench.cpp
//

#include "split.h"
#include <benchmark/benchmark.h>

static void BM_SplitOriginal(benchmark::State &state) {
  for (auto _ : state)
    split("11.22.33.44", '.');
}
BENCHMARK(BM_SplitOriginal);

BENCHMARK_MAIN();
