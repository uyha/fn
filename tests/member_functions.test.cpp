//
// Created by uyha on 23.09.2020.
//
#include "common.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <river/fn.hpp>

using namespace river;

template <typename...>
struct [[maybe_unused]] print_types;

TEST_CASE("Member pointer can be call with any type of object when using overloading_fn") {
  A lvalue{0};
  A const const_lvalue{0};
  A volatile volatile_lvalue{0};
  A const volatile cv_lvalue{0};
  CHECK(over_fn<&A::a>{}(lvalue) == 0);
  CHECK(over_fn<&A::a>{}(const_lvalue) == 0);
  CHECK(over_fn<&A::a>{}(volatile_lvalue) == 0);
  CHECK(over_fn<&A::a>{}(cv_lvalue) == 0);
  CHECK(over_fn<&A::a>{}(std::move(lvalue)) == 0);
  CHECK(over_fn<&A::a>{}(std::move(const_lvalue)) == 0);
  CHECK(over_fn<&A::a>{}(std::move(volatile_lvalue)) == 0);
  CHECK(over_fn<&A::a>{}(std::move(cv_lvalue)) == 0);
}

TEST_CASE("over_fn can be called with the appropriate argument according to C++ rules") {
  A lvalue{0};
  A const const_lvalue{0};
  A volatile volatile_lvalue{0};
  A const volatile cv_lvalue{0};

  SECTION("Functions that are not reference qualified can be called with lvalue and rvalue") {
    CHECK(over_fn<&A::fn>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_const>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_volatile>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_const_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_volatile_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(lvalue) == 0);

    CHECK(over_fn<&A::fn>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_const>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_volatile>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_volatile_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(std::move(lvalue)) == 0);
  }
  SECTION("Reference qualified functions can be called with appropriate lvalue, rvalue") {
    CHECK(over_fn<&A::lvalue_fn>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_volatile>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_volatile_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(lvalue) == 0);

    CHECK(over_fn<&A::rvalue_fn>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_volatile>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(lvalue)) == 0);
  }
  SECTION("const qualified functions that are not reference qualified can be called with const qualified lvalues, "
          "rvalues") {
    CHECK(over_fn<&A::fn_const>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_const>{}(const_lvalue) == 0);
    CHECK(over_fn<&A::fn_const>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_const>{}(std::move(const_lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_const_noexcept>{}(const_lvalue) == 0);
    CHECK(over_fn<&A::fn_const_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_noexcept>{}(std::move(const_lvalue)) == 0);

    CHECK(over_fn<&A::lvalue_fn_const>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const>{}(const_lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_noexcept>{}(const_lvalue) == 0);

#if __cplusplus >= 202002L
    CHECK(over_fn<&A::lvalue_fn_const>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::lvalue_fn_const>{}(std::move(const_lvalue)) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_noexcept>{}(std::move(const_lvalue)) == 0);
#endif

    CHECK(over_fn<&A::rvalue_fn_const>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const>{}(std::move(const_lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_noexcept>{}(std::move(const_lvalue)) == 0);
  }
  SECTION(
      "volatile qualified functions that are not reference qualified can be called with volatile qualified lvalues, "
      "rvalues") {
    CHECK(over_fn<&A::fn_volatile>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_volatile>{}(volatile_lvalue) == 0);
    CHECK(over_fn<&A::fn_volatile>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_volatile>{}(std::move(volatile_lvalue)) == 0);
    CHECK(over_fn<&A::fn_volatile_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_volatile_noexcept>{}(volatile_lvalue) == 0);
    CHECK(over_fn<&A::fn_volatile_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_volatile_noexcept>{}(std::move(volatile_lvalue)) == 0);

    CHECK(over_fn<&A::lvalue_fn_volatile>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_volatile>{}(volatile_lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_volatile_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_volatile_noexcept>{}(volatile_lvalue) == 0);

    CHECK(over_fn<&A::rvalue_fn_volatile>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_volatile>{}(std::move(volatile_lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(volatile_lvalue)) == 0);
  }
  SECTION("cv qualified functions that are not reference qualified can be called with cv qualified lvalues, rvalues") {
    CHECK(over_fn<&A::fn_const_volatile>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(const_lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(volatile_lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(cv_lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(std::move(const_lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(std::move(volatile_lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile>{}(std::move(cv_lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(const_lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(volatile_lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(cv_lvalue) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(std::move(const_lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(std::move(volatile_lvalue)) == 0);
    CHECK(over_fn<&A::fn_const_volatile_noexcept>{}(std::move(cv_lvalue)) == 0);

    CHECK(over_fn<&A::lvalue_fn_const_volatile>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile>{}(const_lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile>{}(volatile_lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile>{}(cv_lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(volatile_lvalue) == 0);
    CHECK(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(cv_lvalue) == 0);

    CHECK(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(const_lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(volatile_lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(cv_lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(const_lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(volatile_lvalue)) == 0);
    CHECK(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(cv_lvalue)) == 0);
  }
}

TEST_CASE("Member functions can be invoke with the object as its first argument") {
  A lvalue{0};
  A const const_lvalue{0};
  A volatile volatile_lvalue{0};
  A const volatile const_volatile_lvalue{0};
  A const to_be_moved{1};
  A volatile to_be_moved_volatile{1};
  A const volatile to_be_moved_const_volatile{1};

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

  CHECK(fn<&A::fn_const>{}(const_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile>{}(const_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const>{}(const_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile>{}(const_lvalue) == 0);
  CHECK(fn<&A::fn_const_noexcept>{}(const_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile_noexcept>{}(const_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_noexcept>{}(const_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_lvalue) == 0);

  CHECK(fn<&A::fn_volatile>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_volatile>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::fn_volatile_noexcept>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::fn_const_volatile_noexcept>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_volatile_noexcept>{}(volatile_lvalue) == 0);
  CHECK(fn<&A::lvalue_fn_const_volatile_noexcept>{}(volatile_lvalue) == 0);

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

  CHECK(fn<&A::fn_const>{}(std::move(to_be_moved)) == 1);
  CHECK(fn<&A::rvalue_fn_const>{}(std::move(to_be_moved)) == 1);
  CHECK(fn<&A::fn_const_noexcept>{}(std::move(to_be_moved)) == 1);
  CHECK(fn<&A::rvalue_fn_const_noexcept>{}(std::move(to_be_moved)) == 1);

  CHECK(fn<&A::rvalue_fn_volatile>{}(std::move(to_be_moved_volatile)) == 1);
  CHECK(fn<&A::rvalue_fn_const_volatile>{}(std::move(to_be_moved_volatile)) == 1);
  CHECK(fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(to_be_moved_volatile)) == 1);
  CHECK(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(to_be_moved_volatile)) == 1);

  CHECK(fn<&A::rvalue_fn_const_volatile>{}(std::move(to_be_moved_const_volatile)) == 1);
  CHECK(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(to_be_moved_const_volatile)) == 1);
}

TEST_CASE("noexcept should be propagated correctly") {
  A lvalue{0};
  A const const_lvalue{0};
  A volatile volatile_lvalue{0};
  A const volatile const_volatile_lvalue{0};

  CHECK(noexcept(fn<&A::fn_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_const_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(lvalue)));

  CHECK(noexcept(fn<&A::fn_const_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_lvalue)));

  CHECK(noexcept(fn<&A::fn_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(volatile_lvalue)));

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

TEST_CASE("noexcept should be propagated") {
  A lvalue{0};
  A const const_lvalue{0};
  A volatile volatile_lvalue{0};
  A const volatile cv_lvalue{0};

  CHECK(noexcept(fn<&A::fn_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_const_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(fn<&A::rvalue_fn_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(lvalue))));

  CHECK_FALSE(noexcept(fn<&A::fn>{}(lvalue)));
  CHECK_FALSE(noexcept(fn<&A::fn_const>{}(lvalue)));
  CHECK_FALSE(noexcept(fn<&A::fn_volatile>{}(lvalue)));
  CHECK_FALSE(noexcept(fn<&A::fn_const_volatile>{}(lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn>{}(lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn_const>{}(lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn_volatile>{}(lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn_const_volatile>{}(lvalue)));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn>{}(std::move(lvalue))));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn_const>{}(std::move(lvalue))));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn_volatile>{}(std::move(lvalue))));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn_const_volatile>{}(std::move(lvalue))));

  CHECK(noexcept(over_fn<&A::fn_noexcept>{}(lvalue)));
  CHECK(noexcept(over_fn<&A::fn_const_noexcept>{}(lvalue)));
  CHECK(noexcept(over_fn<&A::fn_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(over_fn<&A::fn_const_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_noexcept>{}(lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_const_noexcept>{}(lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(lvalue)));
  CHECK(noexcept(over_fn<&A::rvalue_fn_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(over_fn<&A::rvalue_fn_const_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(over_fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(lvalue))));
  CHECK(noexcept(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(lvalue))));

  CHECK_FALSE(noexcept(over_fn<&A::fn>{}(lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::fn_const>{}(lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::fn_volatile>{}(lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::fn_const_volatile>{}(lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn>{}(lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn_const>{}(lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn_volatile>{}(lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn_const_volatile>{}(lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn>{}(std::move(lvalue))));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn_const>{}(std::move(lvalue))));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn_volatile>{}(std::move(lvalue))));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(lvalue))));

  CHECK(noexcept(fn<&A::fn_const_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_lvalue)));
  CHECK(noexcept(fn<&A::rvalue_fn_const_noexcept>{}(std::move(const_lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(const_lvalue))));

  CHECK_FALSE(noexcept(fn<&A::fn_const>{}(const_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::fn_const_volatile>{}(const_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn_const>{}(const_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn_const_volatile>{}(const_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn_const>{}(std::move(const_lvalue))));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn_const_volatile>{}(std::move(const_lvalue))));

  CHECK(noexcept(over_fn<&A::fn_const_noexcept>{}(const_lvalue)));
  CHECK(noexcept(over_fn<&A::fn_const_volatile_noexcept>{}(const_lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_const_noexcept>{}(const_lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(const_lvalue)));
  CHECK(noexcept(over_fn<&A::rvalue_fn_const_noexcept>{}(std::move(const_lvalue))));
  CHECK(noexcept(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(const_lvalue))));

  CHECK_FALSE(noexcept(over_fn<&A::fn_const>{}(const_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::fn_const_volatile>{}(const_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn_const>{}(const_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn_const_volatile>{}(const_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn_const>{}(std::move(const_lvalue))));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(const_lvalue))));

  CHECK(noexcept(fn<&A::fn_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(volatile_lvalue))));
  CHECK(noexcept(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(volatile_lvalue))));

  CHECK_FALSE(noexcept(fn<&A::fn_volatile>{}(volatile_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::fn_const_volatile>{}(volatile_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn_volatile>{}(volatile_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn_const_volatile>{}(volatile_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn_volatile>{}(std::move(volatile_lvalue))));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn_const_volatile>{}(std::move(volatile_lvalue))));

  CHECK(noexcept(over_fn<&A::fn_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(over_fn<&A::fn_const_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(volatile_lvalue)));
  CHECK(noexcept(over_fn<&A::rvalue_fn_volatile_noexcept>{}(std::move(volatile_lvalue))));
  CHECK(noexcept(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(volatile_lvalue))));

  CHECK_FALSE(noexcept(over_fn<&A::fn_volatile>{}(volatile_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::fn_const_volatile>{}(volatile_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn_volatile>{}(volatile_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn_const_volatile>{}(volatile_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn_volatile>{}(std::move(volatile_lvalue))));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(volatile_lvalue))));

  CHECK(noexcept(fn<&A::fn_const_volatile_noexcept>{}(cv_lvalue)));
  CHECK(noexcept(fn<&A::lvalue_fn_const_volatile_noexcept>{}(cv_lvalue)));
  CHECK(noexcept(fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(cv_lvalue))));

  CHECK_FALSE(noexcept(fn<&A::fn_const_volatile>{}(cv_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::lvalue_fn_const_volatile>{}(cv_lvalue)));
  CHECK_FALSE(noexcept(fn<&A::rvalue_fn_const_volatile>{}(std::move(cv_lvalue))));

  CHECK(noexcept(over_fn<&A::fn_const_volatile_noexcept>{}(cv_lvalue)));
  CHECK(noexcept(over_fn<&A::lvalue_fn_const_volatile_noexcept>{}(cv_lvalue)));
  CHECK(noexcept(over_fn<&A::rvalue_fn_const_volatile_noexcept>{}(std::move(cv_lvalue))));

  CHECK_FALSE(noexcept(over_fn<&A::fn_const_volatile>{}(cv_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::lvalue_fn_const_volatile>{}(cv_lvalue)));
  CHECK_FALSE(noexcept(over_fn<&A::rvalue_fn_const_volatile>{}(std::move(cv_lvalue))));
}

TEST_CASE("Fn with member functions") {
  A lvalue{0};
  A const const_lvalue{0};
  A volatile volatile_lvalue{0};
  A const volatile cv_lvalue{0};

  SECTION("object can be passed as first argument to be called") {
    SECTION("lvalue can be called with any lvalue function") {
      CHECK(Fn{&A::fn}(lvalue) == lvalue.a);
      CHECK(Fn{&A::fn_const}(lvalue) == lvalue.a);
      CHECK(Fn{&A::fn_volatile}(lvalue) == lvalue.a);
      CHECK(Fn{&A::fn_const_volatile}(lvalue) == lvalue.a);
      CHECK(Fn{&A::fn_noexcept}(lvalue) == lvalue.a);
      CHECK(Fn{&A::fn_const_noexcept}(lvalue) == lvalue.a);
      CHECK(Fn{&A::fn_volatile_noexcept}(lvalue) == lvalue.a);
      CHECK(Fn{&A::fn_const_volatile_noexcept}(lvalue) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn}(lvalue) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const}(lvalue) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_volatile}(lvalue) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_volatile}(lvalue) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_noexcept}(lvalue) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_noexcept}(lvalue) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_volatile_noexcept}(lvalue) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_volatile_noexcept}(lvalue) == lvalue.a);
    }
    SECTION("const lvalue can be called with any const lvalue function") {
      CHECK(Fn{&A::fn_const}(const_lvalue) == const_lvalue.a);
      CHECK(Fn{&A::fn_const_volatile}(const_lvalue) == const_lvalue.a);
      CHECK(Fn{&A::fn_const_noexcept}(const_lvalue) == const_lvalue.a);
      CHECK(Fn{&A::fn_const_volatile_noexcept}(const_lvalue) == const_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const}(const_lvalue) == const_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_volatile}(const_lvalue) == const_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_noexcept}(const_lvalue) == const_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_volatile_noexcept}(const_lvalue) == const_lvalue.a);
    }
    SECTION("volatile lvalue can be called with any volatile lvalue function") {
      CHECK(Fn{&A::fn_volatile}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(Fn{&A::fn_const_volatile}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(Fn{&A::fn_volatile_noexcept}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(Fn{&A::fn_const_volatile_noexcept}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_volatile}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_volatile}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_volatile_noexcept}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_volatile_noexcept}(volatile_lvalue) == volatile_lvalue.a);
    }
    SECTION("const volatile lvalue can be called with any const volatile lvalue function") {
      CHECK(Fn{&A::fn_const_volatile}(cv_lvalue) == cv_lvalue.a);
      CHECK(Fn{&A::fn_const_volatile_noexcept}(cv_lvalue) == cv_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_volatile}(cv_lvalue) == cv_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_volatile_noexcept}(cv_lvalue) == cv_lvalue.a);
    }
    SECTION("rvalue can be called with any rvalue function") {
      CHECK(Fn{&A::fn_const}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::fn_const_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::rvalue_fn}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::rvalue_fn_volatile}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_volatile}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::rvalue_fn_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::rvalue_fn_volatile_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_volatile_noexcept}(std::move(lvalue)) == lvalue.a);
    }
    SECTION("const rvalue can be called with any const rvalue function") {
      CHECK(Fn{&A::fn_const}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(Fn{&A::fn_const_noexcept}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(Fn{&A::lvalue_fn_const_noexcept}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_volatile}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_noexcept}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_volatile_noexcept}(std::move(const_lvalue)) == const_lvalue.a);
    }
    SECTION("volatile rvalue can be called with any volatile rvalue function") {
      CHECK(Fn{&A::rvalue_fn_volatile}(std::move(volatile_lvalue)) == volatile_lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_volatile}(std::move(volatile_lvalue)) == volatile_lvalue.a);
      CHECK(Fn{&A::rvalue_fn_volatile_noexcept}(std::move(volatile_lvalue)) == volatile_lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_volatile_noexcept}(std::move(volatile_lvalue)) == volatile_lvalue.a);
    }
    SECTION("const volatile rvalue can be called with any const volatile rvalue function") {
      CHECK(Fn{&A::rvalue_fn_const_volatile}(std::move(cv_lvalue)) == cv_lvalue.a);
      CHECK(Fn{&A::rvalue_fn_const_volatile_noexcept}(std::move(cv_lvalue)) == cv_lvalue.a);
    }
  }

  SECTION("noexcept shall be propagated") {
    STATIC_CHECK_FALSE(noexcept(Fn{&A::fn}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::fn_const}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::fn_volatile}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::fn_const_volatile}(lvalue)));

    STATIC_CHECK(noexcept(Fn{&A::fn_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(Fn{&A::fn_const_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(Fn{&A::fn_volatile_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(Fn{&A::fn_const_volatile_noexcept}(lvalue)));

    STATIC_CHECK_FALSE(noexcept(Fn{&A::lvalue_fn}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::lvalue_fn_const}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::lvalue_fn_volatile}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::lvalue_fn_const_volatile}(lvalue)));

    STATIC_CHECK(noexcept(Fn{&A::lvalue_fn_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(Fn{&A::lvalue_fn_const_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(Fn{&A::lvalue_fn_volatile_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(Fn{&A::lvalue_fn_const_volatile_noexcept}(lvalue)));

    STATIC_CHECK_FALSE(noexcept(Fn{&A::rvalue_fn}(std::move(lvalue))));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::rvalue_fn_const}(std::move(lvalue))));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::rvalue_fn_volatile}(std::move(lvalue))));
    STATIC_CHECK_FALSE(noexcept(Fn{&A::rvalue_fn_const_volatile}(std::move(lvalue))));

    STATIC_CHECK(noexcept(Fn{&A::rvalue_fn_noexcept}(std::move(lvalue))));
    STATIC_CHECK(noexcept(Fn{&A::rvalue_fn_const_noexcept}(std::move(lvalue))));
    STATIC_CHECK(noexcept(Fn{&A::rvalue_fn_volatile_noexcept}(std::move(lvalue))));
    STATIC_CHECK(noexcept(Fn{&A::rvalue_fn_const_volatile_noexcept}(std::move(lvalue))));
  }
}

TEST_CASE("OverFn with member functions") {
  A lvalue{0};
  A const const_lvalue{0};
  A volatile volatile_lvalue{0};
  A const volatile cv_lvalue{0};

  SECTION("object can be passed as first argument to be called") {
    SECTION("lvalue can be called with any lvalue function") {
      CHECK(OverFn{&A::fn}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::fn_const}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::fn_volatile}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::fn_const_volatile}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::fn_noexcept}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::fn_const_noexcept}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::fn_volatile_noexcept}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::fn_const_volatile_noexcept}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_volatile}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_volatile}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_noexcept}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_noexcept}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_volatile_noexcept}(lvalue) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_volatile_noexcept}(lvalue) == lvalue.a);
    }
    SECTION("const lvalue can be called with any const lvalue function") {
      CHECK(OverFn{&A::fn_const}(const_lvalue) == const_lvalue.a);
      CHECK(OverFn{&A::fn_const_volatile}(const_lvalue) == const_lvalue.a);
      CHECK(OverFn{&A::fn_const_noexcept}(const_lvalue) == const_lvalue.a);
      CHECK(OverFn{&A::fn_const_volatile_noexcept}(const_lvalue) == const_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const}(const_lvalue) == const_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_volatile}(const_lvalue) == const_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_noexcept}(const_lvalue) == const_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_volatile_noexcept}(const_lvalue) == const_lvalue.a);
    }
    SECTION("volatile lvalue can be called with any volatile lvalue function") {
      CHECK(OverFn{&A::fn_volatile}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(OverFn{&A::fn_const_volatile}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(OverFn{&A::fn_volatile_noexcept}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(OverFn{&A::fn_const_volatile_noexcept}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_volatile}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_volatile}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_volatile_noexcept}(volatile_lvalue) == volatile_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_volatile_noexcept}(volatile_lvalue) == volatile_lvalue.a);
    }
    SECTION("const volatile lvalue can be called with any const volatile lvalue function") {
      CHECK(OverFn{&A::fn_const_volatile}(cv_lvalue) == cv_lvalue.a);
      CHECK(OverFn{&A::fn_const_volatile_noexcept}(cv_lvalue) == cv_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_volatile}(cv_lvalue) == cv_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_volatile_noexcept}(cv_lvalue) == cv_lvalue.a);
    }
    SECTION("rvalue can be called with any rvalue function") {
      CHECK(OverFn{&A::fn_const}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::fn_const_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::rvalue_fn}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_volatile}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_volatile}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_volatile_noexcept}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_volatile_noexcept}(std::move(lvalue)) == lvalue.a);

#if __cplusplus >= 202002L
      CHECK(OverFn{&A::lvalue_fn_const}(std::move(lvalue)) == lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_noexcept}(std::move(lvalue)) == lvalue.a);
#endif
    }
    SECTION("const rvalue can be called with any const rvalue function") {
      CHECK(OverFn{&A::fn_const}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(OverFn{&A::fn_const_noexcept}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_volatile}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_noexcept}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_volatile_noexcept}(std::move(const_lvalue)) == const_lvalue.a);

#if __cplusplus >= 202002L
      CHECK(OverFn{&A::lvalue_fn_const}(std::move(const_lvalue)) == const_lvalue.a);
      CHECK(OverFn{&A::lvalue_fn_const_noexcept}(std::move(const_lvalue)) == const_lvalue.a);
#endif
    }
    SECTION("volatile rvalue can be called with any volatile rvalue function") {
      CHECK(OverFn{&A::rvalue_fn_volatile}(std::move(volatile_lvalue)) == volatile_lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_volatile}(std::move(volatile_lvalue)) == volatile_lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_volatile_noexcept}(std::move(volatile_lvalue)) == volatile_lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_volatile_noexcept}(std::move(volatile_lvalue)) == volatile_lvalue.a);
    }
    SECTION("const volatile rvalue can be called with any const volatile rvalue function") {
      CHECK(OverFn{&A::rvalue_fn_const_volatile}(std::move(cv_lvalue)) == cv_lvalue.a);
      CHECK(OverFn{&A::rvalue_fn_const_volatile_noexcept}(std::move(cv_lvalue)) == cv_lvalue.a);
    }
  }

  SECTION("noexcept shall be propagated") {
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::fn}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::fn_const}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::fn_volatile}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::fn_const_volatile}(lvalue)));

    STATIC_CHECK(noexcept(OverFn{&A::fn_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(OverFn{&A::fn_const_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(OverFn{&A::fn_volatile_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(OverFn{&A::fn_const_volatile_noexcept}(lvalue)));

    STATIC_CHECK_FALSE(noexcept(OverFn{&A::lvalue_fn}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::lvalue_fn_const}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::lvalue_fn_volatile}(lvalue)));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::lvalue_fn_const_volatile}(lvalue)));

    STATIC_CHECK(noexcept(OverFn{&A::lvalue_fn_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(OverFn{&A::lvalue_fn_const_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(OverFn{&A::lvalue_fn_volatile_noexcept}(lvalue)));
    STATIC_CHECK(noexcept(OverFn{&A::lvalue_fn_const_volatile_noexcept}(lvalue)));

    STATIC_CHECK_FALSE(noexcept(OverFn{&A::rvalue_fn}(std::move(lvalue))));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::rvalue_fn_const}(std::move(lvalue))));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::rvalue_fn_volatile}(std::move(lvalue))));
    STATIC_CHECK_FALSE(noexcept(OverFn{&A::rvalue_fn_const_volatile}(std::move(lvalue))));

    STATIC_CHECK(noexcept(OverFn{&A::rvalue_fn_noexcept}(std::move(lvalue))));
    STATIC_CHECK(noexcept(OverFn{&A::rvalue_fn_const_noexcept}(std::move(lvalue))));
    STATIC_CHECK(noexcept(OverFn{&A::rvalue_fn_volatile_noexcept}(std::move(lvalue))));
    STATIC_CHECK(noexcept(OverFn{&A::rvalue_fn_const_volatile_noexcept}(std::move(lvalue))));
  }
}
