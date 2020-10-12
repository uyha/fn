//
// Created by uyha on 06.10.2020.
//

#include "functions.hpp"

#include <benchmark/benchmark.h>

#define BM(fn_name)                                                                                                    \
  static void BM_##fn_name(benchmark::State &state) {                                                                  \
    for (auto _ : state) {                                                                                             \
      fn_name();                                                                                                       \
    }                                                                                                                  \
  }                                                                                                                    \
  BENCHMARK(BM_##fn_name); // NOLINT(cert-err58-cpp)

#define BM_NOOPT(fn_name)                                                                                              \
  static void BM_##fn_name(benchmark::State &state) {                                                                  \
    for (auto _ : state) {                                                                                             \
      benchmark::DoNotOptimize(fn_name());                                                                             \
    }                                                                                                                  \
  }                                                                                                                    \
  BENCHMARK(BM_##fn_name); // NOLINT(cert-err58-cpp)

BM(inline_empty)
BM(inline_empty_noexcept)
BM_NOOPT(inline_const_value)
BM_NOOPT(inline_const_value_noexcept)

BM(empty)
BM(empty_noexcept)
BM_NOOPT(const_value)
BM_NOOPT(const_value_noexcept)

BENCHMARK_MAIN();
