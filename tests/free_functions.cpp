//
// Created by uyha on 23.09.2020.
//

#include <catch2/catch.hpp>
#include <fn/fn.hpp>

int fn_impl() {
  return 1;
}
int diff_fn_impl() {
  return 1;
}

int fn_noexcept_impl() noexcept {
  return 1;
}

void fn_with_argument_impl(int) {}

TEST_CASE("fn of free function pointers can be called with the correct arguments and propagate "
          "noexcept properly") {
  auto test = fn::fn<&fn_impl>();
  CHECK(test() == 1);
  CHECK_FALSE(noexcept(test()));

  auto test_noexcept = fn::fn<&fn_noexcept_impl>();
  CHECK(test_noexcept() == 1);
  CHECK(noexcept(test_noexcept()));

  auto test_with_argument = fn::fn<&fn_with_argument_impl>();
  CHECK(std::is_same_v<decltype(test_with_argument(1)), void>);
  CHECK_FALSE(noexcept(test_with_argument(1)));
}

TEST_CASE("fn of two different function pointers are different types") {
  CHECK_FALSE(std::is_same_v<fn::fn<&fn_impl>, fn::fn<&diff_fn_impl>>);
}