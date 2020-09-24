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

TEST_CASE("fn of free function pointers can be called with the correct arguments") {
  CHECK(fn::fn<&fn_impl>{}() == 1);
  CHECK(fn::fn<&fn_noexcept_impl>{}() == 1);
  CHECK(std::is_same_v<decltype(fn::fn<&fn_with_argument_impl>{}(1)), void>);
}

#if FN_PROPAGATE_NOEXCEPT
TEST_CASE("noexcept should be propagated correctly") {
  CHECK_FALSE(noexcept(fn::fn<&fn_impl>{}()));
  CHECK(noexcept(fn::fn<&fn_noexcept_impl>{}()));
  CHECK_FALSE(noexcept(fn::fn<&fn_with_argument_impl>{}(1)));
}
#endif

TEST_CASE("fn of two different function pointers are different types") {
  CHECK_FALSE(std::is_same_v<fn::fn<&fn_impl>, fn::fn<&diff_fn_impl>>);
}