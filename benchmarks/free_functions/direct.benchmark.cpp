//
// Created by uyha on 06.10.2020.
//

#include "functions.hpp"

#include <benchmark/benchmark.h>

// region inline
static void BM_inline_empty(benchmark::State &state) {
  for (auto _ : state) {
    inline_empty();
  }
}
BENCHMARK(BM_inline_empty); // NOLINT(cert-err58-cpp)

static void BM_inline_empty_noexcept(benchmark::State &state) {
  for (auto _ : state) {
    inline_empty_noexcept();
  }
}
BENCHMARK(BM_inline_empty_noexcept); // NOLINT(cert-err58-cpp)

static void BM_inline_const_value(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(inline_const_value());
  }
}
BENCHMARK(BM_inline_const_value); // NOLINT(cert-err58-cpp)

static void BM_inline_const_value_noexcept(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(inline_const_value_noexcept());
  }
}
BENCHMARK(BM_inline_const_value_noexcept); // NOLINT(cert-err58-cpp)
// endregion

// region outline
static void BM_empty(benchmark::State &state) {
  for (auto _ : state) {
    empty();
  }
}
BENCHMARK(BM_empty); // NOLINT(cert-err58-cpp)

static void BM_const_value(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(const_value());
  }
}
BENCHMARK(BM_const_value); // NOLINT(cert-err58-cpp)
// endregion

BENCHMARK_MAIN();
