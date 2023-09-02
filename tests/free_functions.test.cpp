//
// Created by uyha on 23.09.2020.
//

#include "common.hpp"

#include <catch2/catch_test_macros.hpp>
#include <river/fn.hpp>

TEST_CASE("fn of free function pointers can be called with the correct arguments") {
  CHECK(river::fn<fn1>(0) == 1);
  CHECK(river::fn<fn_noexcept>(0, 0) == 1);

  CHECK(river::over_fn<fn1>(0) == 1);
  CHECK(river::over_fn<fn_noexcept>(0, 0) == 1);
}

TEST_CASE("noexcept should be propagated") {
  CHECK(noexcept(river::fn<fn_noexcept>(0, 0)));
  CHECK_FALSE(noexcept(river::fn<fn1>(0)));
  CHECK(noexcept(river::over_fn<fn_noexcept>(0, 0)));
  CHECK_FALSE(noexcept(river::over_fn<fn1>(0)));
}

TEST_CASE("fn of two different function pointers are different types") {
  CHECK_FALSE(std::is_same_v<decltype(river::fn<fn1>), decltype(river::fn<fn2>)>);
}

TEST_CASE("Fn of free function pointers can be called with the correct arguments") {
  CHECK(river::Fn{fn1}(0) == 1);
  CHECK(river::Fn{fn_noexcept}(0, 0) == 1);
}

TEST_CASE("Fn shall propagate noexcept") {
  CHECK(noexcept(river::Fn{fn_noexcept}(0, 0)));
  CHECK_FALSE(noexcept(river::Fn{fn1}(0)));
}
