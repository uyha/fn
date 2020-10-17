//
// Created by uyha on 06.10.2020.
//

#pragma once
#include <array>
#include <cstdint>
#include <vector>
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
inline std::int64_t inline_array_100_const_ref(std::array<std::int64_t, 100> const &input) {
  return input[0];
}
inline std::int64_t inline_vector_value(std::vector<std::int64_t> input) {
  return input[0];
}
inline std::int64_t inline_vector_const_ref(std::vector<std::int64_t> const &input) {
  return input[0];
}

void empty();
void empty_noexcept() noexcept;
int const_value();
int const_value_noexcept() noexcept;
std::int64_t one_arg(int64_t input);
std::int64_t array_100(std::array<std::int64_t, 100> input);
std::int64_t array_100_const_ref(std::array<std::int64_t, 100> const &input);
std::int64_t vector_value(std::vector<std::int64_t> input);
std::int64_t vector_const_ref(std::vector<std::int64_t> const &input);
