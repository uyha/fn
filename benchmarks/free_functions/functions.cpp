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
