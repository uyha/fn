//
// Created by uyha on 06.10.2020.
//
#include "functions.hpp"

#include <benchmark/benchmark.h>
#include <river/fn.hpp>

#define BM(fn_name)                                                                                                    \
  static void BM_##fn_name(benchmark::State &state) {                                                                  \
    for (auto _ : state) {                                                                                             \
      auto const f = fn<&fn_name>{};                                                                                   \
      f();                                                                                                             \
    }                                                                                                                  \
  }                                                                                                                    \
  BENCHMARK(BM_##fn_name); // NOLINT(cert-err58-cpp)

#define BM_NOOPT(fn_name)                                                                                              \
  static void BM_##fn_name(benchmark::State &state) {                                                                  \
    for (auto _ : state) {                                                                                             \
      auto const f = fn<&fn_name>{};                                                                                   \
      benchmark::DoNotOptimize(f());                                                                                   \
    }                                                                                                                  \
  }                                                                                                                    \
  BENCHMARK(BM_##fn_name); // NOLINT(cert-err58-cpp)

#define BM_ARG(fn_name, arg)                                                                                           \
  static void BM_##fn_name(benchmark::State &state) {                                                                  \
    for (auto _ : state) {                                                                                             \
      auto const f = fn<&fn_name>{};                                                                                   \
      benchmark::DoNotOptimize(f(arg));                                                                                \
    }                                                                                                                  \
  }                                                                                                                    \
  BENCHMARK(BM_##fn_name)
using namespace river;

static_assert(std::is_same_v<fn_trait_of<&inline_empty_noexcept>::return_type, void>);

BM(inline_empty)
BM(inline_empty_noexcept)
BM_NOOPT(inline_const_value)
BM_NOOPT(inline_const_value_noexcept)
BM_ARG(inline_one_arg, state.range(0))->Arg(1); // NOLINT(cert-err58-cpp)

BM(empty)
BM(empty_noexcept)
BM_NOOPT(const_value)
BM_NOOPT(const_value_noexcept)
BM_ARG(one_arg, state.range(0))->Arg(1); // NOLINT(cert-err58-cpp)

BENCHMARK_MAIN();