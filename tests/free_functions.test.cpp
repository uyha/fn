//
// Created by uyha on 23.09.2020.
//

#include <catch2/catch.hpp>
#include <fn/fn.hpp>

int fn() {
  return 1;
}
int diff_fn() {
  return 1;
}

int fn_noexcept() noexcept {
  return 1;
}

void fn_with_argument(int) {}

TEST_CASE("fn of free function pointers can be called with the correct arguments") {
  CHECK(river::fn<&fn>{}() == 1);
  CHECK(river::fn<&fn_noexcept>{}() == 1);
  CHECK(std::is_same_v<decltype(river::fn<&fn_with_argument>{}(1)), void>);

  CHECK(river::overloading_fn<&fn>{}() == 1);
  CHECK(river::overloading_fn<&fn_noexcept>{}() == 1);
  CHECK(std::is_same_v<decltype(river::overloading_fn<&fn_with_argument>{}(1)), void>);
}

TEST_CASE("noexcept should be propagated") {
  CHECK(noexcept(river::fn<&fn_noexcept>{}()));
  CHECK_FALSE(noexcept(river::fn<&fn>{}()));
  CHECK(noexcept(river::overloading_fn<&fn_noexcept>{}()));
  CHECK_FALSE(noexcept(river::overloading_fn<&fn>{}()));
}

TEST_CASE("fn of two different function pointers are different types") {
  CHECK_FALSE(std::is_same_v<river::fn<&fn>, river::fn<&diff_fn>>);
}