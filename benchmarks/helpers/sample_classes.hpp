//
// Created by uyha on 12.10.2020.
//

#pragma once
#include <array>

struct ECopyEMove {
  std::array<int, 5000> expensive_member{};
};