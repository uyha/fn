//
// Created by uyha on 06.10.2020.
//

#pragma once
#include <array>
#include <cstdint>
inline void inline_empty() {}
inline void inline_empty_noexcept() noexcept {}
inline int inline_const_value() {
  return 42;
}
inline int inline_const_value_noexcept() noexcept {
  return 42;
}
inline std::int64_t inline_one_arg(std::int64_t input) {
  return input;
}
inline std::int64_t inline_array_100(std::array<std::int64_t, 100> input) {
  return input[0];
}

void empty();
void empty_noexcept() noexcept;
int const_value();
int const_value_noexcept() noexcept;
std::int64_t one_arg(int64_t input);
