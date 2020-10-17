//
// Created by uyha on 16.10.2020.
//

#pragma once
#define THIRD_ARG(a, b, c, ...) c
#define HAS_VA_OPT_IMPL(...) THIRD_ARG(__VA_OPT__(, ), 1, 0)
#define HAS_VA_OPT HAS_VA_OPT_IMPL(?)

#if !HAS_VA_OPT
#error "Support for __VA_OPT__ is required to compile the benchmark code"
#endif

#define DIRECT 0
#define WRAP 1

#define ID(fn) fn
#define NOOPT(fn) benchmark::DoNotOptimize(fn)

#define DR(fn_name) &fn_name
#define FN(fn_name)                                                                                                    \
  river::fn<&fn_name> {}

#define BM(construct, opt, fn_name)                                                                                    \
  static void BM_##fn_name(benchmark::State &state) {                                                                  \
    for (auto _ : state) {                                                                                             \
      constexpr auto f = construct(fn_name);                                                                           \
      opt(f());                                                                                                        \
    }                                                                                                                  \
  }                                                                                                                    \
  BENCHMARK(BM_##fn_name)

#define BM_ARG(construct, opt, fn_name, first_arg, ...)                                                                \
  template <typename... Args>                                                                                          \
  void BM_##fn_name(benchmark::State &state, Args &&... args) {                                                        \
    for (auto _ : state) {                                                                                             \
      constexpr auto f = construct(fn_name);                                                                           \
      opt(fn_name(args...));                                                                                           \
    }                                                                                                                  \
  }                                                                                                                    \
  BENCHMARK_CAPTURE(BM_##fn_name, , first_arg __VA_OPT__(, ) __VA_ARGS__)
