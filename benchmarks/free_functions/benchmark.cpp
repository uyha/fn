//
// Created by uyha on 06.10.2020.
//

#include "functions.hpp"
#include "helper.hpp"
#include "sample_classes.hpp"

#include <benchmark/benchmark.h>

#ifndef MODE
#error "Please define a mode for benchmarking (either DR or FN)"
#endif

#if MODE == DIRECT
#define CALL DR
#elif MODE == WRAP
#include <river/fn.hpp>
#define CALL FN
#else
#error "Unknown call mode"
#endif

BM(CALL, ID, inline_empty);                                                       // NOLINT(cert-err58-cpp)
BM(CALL, ID, inline_empty_noexcept);                                              // NOLINT(cert-err58-cpp)
BM(CALL, NOOPT, inline_const_value);                                              // NOLINT(cert-err58-cpp)
BM(CALL, NOOPT, inline_const_value_noexcept);                                     // NOLINT(cert-err58-cpp)
BM_ARG(CALL, NOOPT, inline_one_arg, 1);                                           // NOLINT(cert-err58-cpp)
BM_ARG(CALL, NOOPT, inline_array_100, std::array<std::int64_t, 100>{});           // NOLINT(cert-err58-cpp)
BM_ARG(CALL, NOOPT, inline_array_100_const_ref, std::array<std::int64_t, 100>{}); // NOLINT(cert-err58-cpp)

BM(CALL, ID, empty);                                                       // NOLINT(cert-err58-cpp)
BM(CALL, ID, empty_noexcept);                                              // NOLINT(cert-err58-cpp)
BM(CALL, NOOPT, const_value);                                              // NOLINT(cert-err58-cpp)
BM(CALL, NOOPT, const_value_noexcept);                                     // NOLINT(cert-err58-cpp)
BM_ARG(CALL, NOOPT, one_arg, 1);                                           // NOLINT(cert-err58-cpp)
BM_ARG(CALL, NOOPT, array_100, std::array<std::int64_t, 100>{});           // NOLINT(cert-err58-cpp)
BM_ARG(CALL, NOOPT, array_100_const_ref, std::array<std::int64_t, 100>{}); // NOLINT(cert-err58-cpp)

BENCHMARK_MAIN();
