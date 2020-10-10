//
// Created by uyha on 06.10.2020.
//
#include "functions.hpp"

#include <benchmark/benchmark.h>
#include <river/fn.hpp>

using namespace river;

// region inline
static void BM_inline_empty(benchmark::State &state) {
  for (auto _ : state) {
    auto const f = fn<&inline_empty>{};
    f();
  }
}
BENCHMARK(BM_inline_empty); // NOLINT(cert-err58-cpp)

static void BM_inline_empty_noexcept(benchmark::State &state) {
  for (auto _ : state) {
    auto const f = fn<&inline_empty_noexcept>{};
    f();
  }
}
BENCHMARK(BM_inline_empty_noexcept); // NOLINT(cert-err58-cpp)

static void BM_inline_const_value(benchmark::State &state) {
  for (auto _ : state) {
    auto const f = fn<&inline_const_value>{};
    benchmark::DoNotOptimize(f());
  }
}
BENCHMARK(BM_inline_const_value); // NOLINT(cert-err58-cpp)

static void BM_inline_const_value_noexcept(benchmark::State &state) {
  for (auto _ : state) {
    auto const f = fn<&inline_const_value_noexcept>{};
    benchmark::DoNotOptimize(f());
  }
}
BENCHMARK(BM_inline_const_value_noexcept); // NOLINT(cert-err58-cpp)
// endregion

// region outline
static void BM_empty(benchmark::State &state) {
  for (auto _ : state) {
    auto const f = fn<&empty>{};
    f();
  }
}
BENCHMARK(BM_empty); // NOLINT(cert-err58-cpp)

static void BM_const_value(benchmark::State &state) {
  for (auto _ : state) {
    auto const f = fn<&const_value>{};
    benchmark::DoNotOptimize(f());
  }
}
BENCHMARK(BM_const_value); // NOLINT(cert-err58-cpp)
// endregion

BENCHMARK_MAIN();