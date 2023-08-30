#include <catch2/catch_test_macros.hpp>
#include <fmt/printf.h>
#include <river/fn.hpp>
#include <utility>

struct UserClass {
  auto operator()(int){};

  int a = 1;
};

using namespace river;

struct A {
  auto operator()() const {
    return 1;
  }
};

TEST_CASE("fn_trait_of invocables will look at its operator() if possible, then it will look at the given value") {
  constexpr auto lambda = [] {};

  STATIC_CHECK(std::is_same_v<fn_trait_of<lambda>, fn_trait<void (decltype(lambda)::*)() const>>);
  STATIC_CHECK(std::is_same_v<fn_trait_of<UserClass{}>, fn_trait<void (UserClass::*)(int)>>);
  STATIC_CHECK(std::is_same_v<fn_trait_of<&UserClass::a>, fn_trait<int UserClass::*>>);
}

TEST_CASE("fn works with invocables") {
  STATIC_CHECK(fn<[] { return 1; }>{}() == 1);
  CHECK(overloading_fn<A{}>{}() == 1);
}
