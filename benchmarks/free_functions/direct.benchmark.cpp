//
// Created by uyha on 06.10.2020.
//

#include "functions.hpp"

#include <benchmark/benchmark.h>

static void BM_inline_empty_function(benchmark::State &state) {
  for (auto _ : state) {
    inline_empty_function();
  }
}
BENCHMARK(BM_inline_empty_function); // NOLINT(cert-err58-cpp)

static void BM_inline_const_value_function(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(inline_const_value_function());
  }
}
BENCHMARK(BM_inline_const_value_function); // NOLINT(cert-err58-cpp)

static void BM_empty_function(benchmark::State &state) {
  for (auto _ : state) {
    empty_function();
  }
}
BENCHMARK(BM_empty_function); // NOLINT(cert-err58-cpp)

static void BM_const_value_function(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(const_value_function());
  }
}
BENCHMARK(BM_const_value_function); // NOLINT(cert-err58-cpp)

BENCHMARK_MAIN();
