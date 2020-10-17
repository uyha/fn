//
// Created by uyha on 06.10.2020.
//

#include "functions.hpp"

void empty() {}
void empty_noexcept() noexcept {}
int const_value() {
  return 42;
}
int const_value_noexcept() noexcept {
  return 42;
}
std::int64_t one_arg(int64_t input) {
  return input;
}
std::int64_t array_100(std::array<std::int64_t, 100> input) {
  return input[0];
}
std::int64_t array_100_const_ref(std::array<std::int64_t, 100> const &input) {
  return input[0];
}
std::int64_t vector_value(std::vector<std::int64_t> input) {
  return input[0];
}
std::int64_t vector_const_ref(std::vector<std::int64_t> const &input) {
  return input[0];
}
