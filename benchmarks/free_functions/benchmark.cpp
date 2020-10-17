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

#if MODE == FN
#include <river/fn.hpp>
#endif

BM(MODE, ID, inline_empty);                   // NOLINT(cert-err58-cpp)
BM(MODE, ID, inline_empty_noexcept);          // NOLINT(cert-err58-cpp)
BM(MODE, NOOPT, inline_const_value);          // NOLINT(cert-err58-cpp)
BM(MODE, NOOPT, inline_const_value_noexcept); // NOLINT(cert-err58-cpp)
BM_ARG(MODE, NOOPT, inline_one_arg, 1);       // NOLINT(cert-err58-cpp)

BM(MODE, ID, empty);                   // NOLINT(cert-err58-cpp)
BM(MODE, ID, empty_noexcept);          // NOLINT(cert-err58-cpp)
BM(MODE, NOOPT, const_value);          // NOLINT(cert-err58-cpp)
BM(MODE, NOOPT, const_value_noexcept); // NOLINT(cert-err58-cpp)
BM_ARG(MODE, NOOPT, one_arg, 1);       // NOLINT(cert-err58-cpp)

BENCHMARK_MAIN();
