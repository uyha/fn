//
// Created by uyha on 23.09.2020.
//
#include <catch2/catch.hpp>
#include <fn/fn.hpp>

using namespace river;

struct A {
  int a;

  int fn() {
    return a;
  }
  int fn_const() const {
    return a;
  }
  int fn_volatile() volatile {
    return a;
  }
  int fn_const_volatile() const volatile {
    return a;
  }
  int fn_noexcept() noexcept {
    return a;
  }
  int fn_const_noexcept() const noexcept {
    return a;
  }
  int fn_volatile_noexcept() volatile noexcept {
    return a;
  }
  int fn_const_volatile_noexcept() const volatile noexcept {
    return a;
  }

  int lvalue_fn() & {
    return a;
  }
  int lvalue_fn_const() const & {
    return a;
  }
  int lvalue_fn_volatile() volatile & {
    return a;
  }
  int lvalue_fn_const_volatile() const volatile & {
    return a;
  }
  int lvalue_fn_noexcept() &noexcept {
    return a;
  }
  int lvalue_fn_const_noexcept() const &noexcept {
    return a;
  }
  int lvalue_fn_volatile_noexcept() volatile &noexcept {
    return a;
  }
  int lvalue_fn_const_volatile_noexcept() const volatile &noexcept {
    return a;
  }

  int rvalue_fn() && {
    return a;
  }
  int rvalue_fn_const() const && {
    return a;
  }
  int rvalue_fn_volatile() volatile && {
    return a;
  }
  int rvalue_fn_const_volatile() const volatile && {
    return a;
  }
  int rvalue_fn_noexcept() &&noexcept {
    return a;
  }
  int rvalue_fn_const_noexcept() const &&noexcept {
    return a;
  }
  int rvalue_fn_volatile_noexcept() volatile &&noexcept {
    return a;
  }
  int rvalue_fn_const_volatile_noexcept() const volatile &&noexcept {
    return a;
  }
};

TEST_CASE("Member functions can be invoke with the object as its first argument") {
  A lvalue{0};
  CHECK(fn<&A::a>{}(lvalue) == 0);
  CHECK(fn<&A::fn>{}(lvalue) == 0);
  CHECK(fn<&A::fn_const>{}(lvalue) == 0);
  CHECK(fn<&A::fn_volatile>{}(lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile>{}(lvalue) == 0);
  CHECK(fn<&A::lvalue_fn>{}(lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const>{}(lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_volatile>{}(lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile>{}(lvalue) == 0);
  CHECK(fn<&A::fn_noexcept>{}(lvalue) == 0);
  CHECK(fn<&A::fn_const_noexcept>{}(lvalue) == 0);
  CHECK(fn<&A::fn_volatile_noexcept>{}(lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile_noexcept>{}(lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_noexcept>{}(lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_noexcept>{}(lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_volatile_noexcept>{}(lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile_noexcept>{}(lvalue) == 0);

  A const const_lvalue{0};
  CHECK(fn<&A::fn_const>{}(const_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile>{}(const_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const>{}(const_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile>{}(const_lvalue) == 0);
  CHECK(fn<&A::fn_const_noexcept>{}(const_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile_noexcept>{}(const_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_noexcept>{}(const_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_lvalue) == 0);

  A volatile volatile_lvalue{0};
  CHECK(fn<&A::fn_volatile>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_volatile>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::fn_volatile_noexcept>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile_noexcept>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_volatile_noexcept>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile_noexcept>{}(volatile_lvalue) == 0);

  A const volatile const_volatile_lvalue{0};
  CHECK(fn<&A::fn_const_volatile>{}(const_volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile>{}(const_volatile_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile_noexcept>{}(const_volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_volatile_lvalue) == 0);

  CHECK(fn<&A::fn_const>{}(A{0}) == 0);
  CHECK(fn<&A::rvalue_fn>{}(A{0}) == 0);
  CHECK(fn<&A::rvalue_fn_const>{}(A{0}) == 0);
  CHECK(fn<&A::rvalue_fn_volatile>{}(A{0}) == 0);
  CHECK(fn<&A::rvalue_fn_const_volatile>{}(A{0}) == 0);
  CHECK(fn<&A::fn_const_noexcept>{}(A{0}) == 0);
  CHECK(fn<&A::rvalue_fn_noexcept>{}(A{0}) == 0);
  CHECK(fn<&A::rvalue_fn_const_noexcept>{}(A{0}) == 0);
  CHECK(fn<&A::rvalue_fn_volatile_noexcept>{}(A{0}) == 0);
  CHECK(fn<&A::rvalue_fn_const_volatile_noexcept>{}(A{0}) == 0);

  A const to_be_moved{1};
  CHECK(fn<&A::fn_const>{}(std::move(to_be_moved)) == 1);
  CHECK(fn<&A::rvalue_fn_const>{}(std::move(to_be_moved)) == 1);
  CHECK(fn<&A::fn_const_noexcept>{}(std::move(to_be_moved)) == 1);
  CHECK(fn<&A::rvalue_fn_const_noexcept>{}(std::move(to_be_moved)) == 1);

  A volatile to_be_moved_volatile{1};
  CHECK(fn<&A::rvalue_fn_volatile>{}(std::move(to_be_moved_volatile)) == 1);
  CHECK(fn<&A::rvalue_fn_const_volatile>{}(std::move(to_be_moved_volatile)) == 1);
  CHECK(fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(to_be_moved_volatile)) == 1);
  CHECK(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(to_be_moved_volatile)) == 1);

  A const volatile to_be_moved_const_volatile{1};
  CHECK(fn<&A::rvalue_fn_const_volatile>{}(std::move(to_be_moved_const_volatile)) == 1);
  CHECK(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(to_be_moved_const_volatile)) == 1);
}

TEST_CASE("noexcept should be propagated correctly") {
  A lvalue{0};
  CHECK(noexcept(fn<&A::fn_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_const_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(lvalue)));

  A const const_lvalue{0};
  CHECK(noexcept(fn<&A::fn_const_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_lvalue)));

  A volatile volatile_lvalue{0};
  CHECK(noexcept(fn<&A::fn_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(volatile_lvalue)));

  A const volatile const_volatile_lvalue{0};
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(const_volatile_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_volatile_lvalue)));

  CHECK(noexcept(fn<&A::fn_const_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(fn<&A::lvalue_fn_const_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(lvalue))));

  CHECK(noexcept(fn<&A::fn_const_noexcept>{}(std::move(const_lvalue))));
  CHECK(noexcept(fn<&A::lvalue_fn_const_noexcept>{}(std::move(const_lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_noexcept>{}(std::move(const_lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(const_lvalue))));

  CHECK(noexcept(fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(volatile_lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(volatile_lvalue))));

  CHECK(noexcept(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(const_volatile_lvalue))));
}
