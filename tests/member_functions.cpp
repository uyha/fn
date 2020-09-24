//
// Created by uyha on 23.09.2020.
//
#include <catch2/catch.hpp>
#include <fn/fn.hpp>

struct A {
  int a;

  int fn() {
    return a;
  }
  int fn_const() const {
    return a;
  }
  int fn_noexcept() noexcept {
    return a;
  }
  int fn_const_noexcept() const noexcept {
    return a;
  }

  int rvalue_fn() && {
    return a;
  }
  int rvalue_fn_const() const && {
    return a;
  }
  int rvalue_fn_noexcept() &&noexcept {
    return a;
  }
  int rvalue_fn_const_noexcept() const &&noexcept {
    return a;
  }
};

TEST_CASE("Member functions can be invoke with the object as its first argument") {
  A zero{0};
  CHECK(fn::fn<&A::fn>{}(zero) == 0);
  CHECK(fn::fn<&A::fn_const>{}(zero) == 0);
  CHECK(fn::fn<&A::fn_noexcept>{}(zero) == 0);
  CHECK(fn::fn<&A::fn_const_noexcept>{}(zero) == 0);

  A const one{1};
  CHECK(fn::fn<&A::fn_const>{}(one) == 1);
  CHECK(fn::fn<&A::fn_const_noexcept>{}(one) == 1);

  CHECK(fn::fn<&A::fn>{}(A{0}) == 0);
  CHECK(fn::fn<&A::fn_const>{}(A{0}) == 0);
  CHECK(fn::fn<&A::fn_noexcept>{}(A{0}) == 0);
  CHECK(fn::fn<&A::fn_const_noexcept>{}(A{0}) == 0);
  CHECK(fn::fn<&A::rvalue_fn>{}(A{0}) == 0);
  CHECK(fn::fn<&A::rvalue_fn_const>{}(A{0}) == 0);
  CHECK(fn::fn<&A::rvalue_fn_noexcept>{}(A{0}) == 0);
  CHECK(fn::fn<&A::rvalue_fn_const_noexcept>{}(A{0}) == 0);

  CHECK(fn::fn<&A::fn_const>{}(std::move(one)) == 1);
  CHECK(fn::fn<&A::fn_const_noexcept>{}(std::move(one)) == 1);
  CHECK(fn::fn<&A::rvalue_fn_const>{}(std::move(one)) == 1);
  CHECK(fn::fn<&A::rvalue_fn_const_noexcept>{}(std::move(one)) == 1);
}

#if FN_PROPAGATE_NOEXCEPT
TEST_CASE("noexcept should be propagated correctly") {
  A zero{0};
  A const one{1};

  CHECK(noexcept(fn::fn<&A::fn_noexcept>{}(zero)));
  CHECK(noexcept(fn::fn<&A::fn_const_noexcept>{}(zero)));
  CHECK(noexcept(fn::fn<&A::fn_const_noexcept>{}(one)));
  CHECK(noexcept(fn::fn<&A::fn_noexcept>{}(A{0})));
  CHECK(noexcept(fn::fn<&A::fn_const_noexcept>{}(A{0})));
  CHECK(noexcept(fn::fn<&A::rvalue_fn_noexcept>{}(A{0})));
  CHECK(noexcept(fn::fn<&A::rvalue_fn_const_noexcept>{}(A{0})));
  CHECK(noexcept(fn::fn<&A::fn_const_noexcept>{}(std::move(one))));
  CHECK(noexcept(fn::fn<&A::rvalue_fn_const_noexcept>{}(std::move(one))));
}
#endif
