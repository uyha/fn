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
  constexpr auto operator()() const {
    return 1;
  }
};

TEST_CASE("fn_trait_of invocables will look at its operator() if possible, then it will look at the given value") {
  constexpr auto lambda = [] {};
  using lambda_type     = decltype(lambda);

  STATIC_CHECK(std::is_same_v<fn_trait_of<lambda>::object_t, fn_trait<decltype(&lambda_type::operator())>::object_t>);
  STATIC_CHECK(std::is_same_v<fn_trait_of<lambda>::return_t, fn_trait<decltype(&lambda_type::operator())>::return_t>);
  STATIC_CHECK(std::is_same_v<fn_trait_of<lambda>::arguments, fn_trait<decltype(&lambda_type::operator())>::arguments>);

  STATIC_CHECK(std::is_same_v<fn_trait_of<A{}>::object_t, fn_trait<decltype(&A::operator())>::object_t>);
  STATIC_CHECK(std::is_same_v<fn_trait_of<A{}>::return_t, fn_trait<decltype(&A::operator())>::return_t>);
  STATIC_CHECK(std::is_same_v<fn_trait_of<A{}>::arguments, fn_trait<decltype(&A::operator())>::arguments>);

  STATIC_CHECK(std::is_same_v<fn_trait_of<&UserClass::a>, fn_trait<int UserClass::*>>);
}

TEST_CASE("fn works with invocables") {
  STATIC_CHECK(fn<[] { return 1; }>() == 1);
  STATIC_CHECK(fn<A{}>() == 1);
  STATIC_CHECK(over_fn<A{}>() == 1);
}

TEST_CASE("Fn works with invocables") {
  constexpr auto lambda = [] { return 1; };
  STATIC_CHECK(Fn{lambda}() == 1);
  STATIC_CHECK(Fn{A{}}() == 1);
}

TEST_CASE("Fn has equal size to invocables") {
  constexpr auto lambda = [] { return 1; };
  STATIC_CHECK(sizeof(Fn<decltype(lambda)>) == sizeof(lambda));
  STATIC_CHECK(sizeof(Fn<A>) == sizeof(A));
}
