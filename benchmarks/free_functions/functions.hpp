//
// Created by uyha on 06.10.2020.
//

#pragma once
inline void inline_empty() {}
inline void inline_empty_noexcept() noexcept {}
inline int inline_const_value() {
  return 42;
}
inline int inline_const_value_noexcept() noexcept {
  return 42;
}

void empty();
void empty_noexcept() noexcept;
int const_value();
int const_value_noexcept() noexcept;
