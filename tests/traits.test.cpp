//
// Created by uyha on 26.09.2020.
//
#include <catch2/catch.hpp>
#include <fn/fn.hpp>

using namespace river;

template <typename...>
struct print_type;

using normal_fn       = void();
using normal_fn_ptr   = void (*)();
using noexcept_fn     = void() noexcept;
using noexcept_fn_ptr = void (*)() noexcept;

struct A {};
using memfn                   = void (A::*)();
using const_memfn             = void (A::*)() const;
using volatile_memfn          = void (A::*)() volatile;
using cv_memfn                = void (A::*)() const volatile;
using noexcept_memfn          = void (A::*)() noexcept;
using noexcept_const_memfn    = void (A::*)() const noexcept;
using noexcept_volatile_memfn = void (A::*)() volatile noexcept;
using noexcept_cv_memfn       = void (A::*)() const volatile noexcept;

using lvalue_memfn                   = void (A::*)() &;
using lvalue_const_memfn             = void (A::*)() const &;
using lvalue_volatile_memfn          = void (A::*)() volatile &;
using lvalue_cv_memfn                = void (A::*)() const volatile &;
using lvalue_noexcept_memfn          = void (A::*)() &noexcept;
using lvalue_noexcept_const_memfn    = void (A::*)() const &noexcept;
using lvalue_noexcept_volatile_memfn = void (A::*)() volatile &noexcept;
using lvalue_noexcept_cv_memfn       = void (A::*)() const volatile &noexcept;

using rvalue_memfn                   = void (A::*)() &&;
using rvalue_const_memfn             = void (A::*)() const &&;
using rvalue_volatile_memfn          = void (A::*)() volatile &&;
using rvalue_cv_memfn                = void (A::*)() const volatile &&;
using rvalue_noexcept_memfn          = void (A::*)() &&noexcept;
using rvalue_noexcept_const_memfn    = void (A::*)() const &&noexcept;
using rvalue_noexcept_volatile_memfn = void (A::*)() volatile &&noexcept;
using rvalue_noexcept_cv_memfn       = void (A::*)() const volatile &&noexcept;

TEST_CASE("remove_noexcept should return the same signature with no noexcept specifier") {
  SECTION("Normal functions") {
    CHECK(std::is_same_v<remove_noexcept_t<noexcept_fn>, normal_fn>);
    CHECK(std::is_same_v<remove_noexcept_t<noexcept_fn_ptr>, normal_fn_ptr>);

    CHECK(std::is_same_v<remove_noexcept_t<normal_fn>, normal_fn>);
    CHECK(std::is_same_v<remove_noexcept_t<normal_fn_ptr>, normal_fn_ptr>);
  }

  SECTION("no reference qualified member functions") {
    CHECK(std::is_same_v<remove_noexcept_t<noexcept_memfn>, memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<noexcept_const_memfn>, const_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<noexcept_volatile_memfn>, volatile_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<noexcept_cv_memfn>, cv_memfn>);

    CHECK(std::is_same_v<remove_noexcept_t<memfn>, memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<const_memfn>, const_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<volatile_memfn>, volatile_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<cv_memfn>, cv_memfn>);
  }

  SECTION("lvalue qualified member functions") {
    CHECK(std::is_same_v<remove_noexcept_t<lvalue_noexcept_memfn>, lvalue_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<lvalue_noexcept_const_memfn>, lvalue_const_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<lvalue_noexcept_volatile_memfn>, lvalue_volatile_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<lvalue_noexcept_cv_memfn>, lvalue_cv_memfn>);

    CHECK(std::is_same_v<remove_noexcept_t<lvalue_memfn>, lvalue_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<lvalue_const_memfn>, lvalue_const_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<lvalue_volatile_memfn>, lvalue_volatile_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<lvalue_cv_memfn>, lvalue_cv_memfn>);
  }

  SECTION("rvalue qualified member functions") {
    CHECK(std::is_same_v<remove_noexcept_t<rvalue_noexcept_memfn>, rvalue_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<rvalue_noexcept_const_memfn>, rvalue_const_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<rvalue_noexcept_volatile_memfn>, rvalue_volatile_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<rvalue_noexcept_cv_memfn>, rvalue_cv_memfn>);

    CHECK(std::is_same_v<remove_noexcept_t<rvalue_memfn>, rvalue_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<rvalue_const_memfn>, rvalue_const_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<rvalue_volatile_memfn>, rvalue_volatile_memfn>);
    CHECK(std::is_same_v<remove_noexcept_t<rvalue_cv_memfn>, rvalue_cv_memfn>);
  }
}

TEST_CASE("is_noexcept trait should return true for noexcept functions and false otherwise") {
  CHECK(is_noexcept_v<noexcept_fn>);
  CHECK(is_noexcept_v<noexcept_fn_ptr>);
  CHECK(is_noexcept_v<noexcept_memfn>);
  CHECK(is_noexcept_v<noexcept_const_memfn>);
  CHECK(is_noexcept_v<noexcept_volatile_memfn>);
  CHECK(is_noexcept_v<noexcept_cv_memfn>);

  CHECK_FALSE(is_noexcept_v<normal_fn>);
  CHECK_FALSE(is_noexcept_v<normal_fn_ptr>);
  CHECK_FALSE(is_noexcept_v<memfn>);
  CHECK_FALSE(is_noexcept_v<const_memfn>);
  CHECK_FALSE(is_noexcept_v<volatile_memfn>);
  CHECK_FALSE(is_noexcept_v<cv_memfn>);
}

TEST_CASE("remove_const should return the same signature with no const specifier") {
  SECTION("No reference qualified member functions") {
    CHECK(std::is_same_v<remove_const_t<const_memfn>, memfn>);
    CHECK(std::is_same_v<remove_const_t<noexcept_const_memfn>, noexcept_memfn>);
    CHECK(std::is_same_v<remove_const_t<cv_memfn>, volatile_memfn>);
    CHECK(std::is_same_v<remove_const_t<noexcept_cv_memfn>, noexcept_volatile_memfn>);

    CHECK(std::is_same_v<remove_const_t<memfn>, memfn>);
    CHECK(std::is_same_v<remove_const_t<noexcept_memfn>, noexcept_memfn>);
    CHECK(std::is_same_v<remove_const_t<volatile_memfn>, volatile_memfn>);
    CHECK(std::is_same_v<remove_const_t<noexcept_volatile_memfn>, noexcept_volatile_memfn>);
  }
  SECTION("lvalue qualified member functions") {
    CHECK(std::is_same_v<remove_const_t<lvalue_const_memfn>, lvalue_memfn>);
    CHECK(std::is_same_v<remove_const_t<lvalue_noexcept_const_memfn>, lvalue_noexcept_memfn>);
    CHECK(std::is_same_v<remove_const_t<lvalue_cv_memfn>, lvalue_volatile_memfn>);
    CHECK(std::is_same_v<remove_const_t<lvalue_noexcept_cv_memfn>, lvalue_noexcept_volatile_memfn>);

    CHECK(std::is_same_v<remove_const_t<lvalue_memfn>, lvalue_memfn>);
    CHECK(std::is_same_v<remove_const_t<lvalue_noexcept_memfn>, lvalue_noexcept_memfn>);
    CHECK(std::is_same_v<remove_const_t<lvalue_volatile_memfn>, lvalue_volatile_memfn>);
    CHECK(std::is_same_v<remove_const_t<lvalue_noexcept_volatile_memfn>,
                         lvalue_noexcept_volatile_memfn>);
  }
  SECTION("rvalue reference qualified member functions") {
    CHECK(std::is_same_v<remove_const_t<rvalue_const_memfn>, rvalue_memfn>);
    CHECK(std::is_same_v<remove_const_t<rvalue_noexcept_const_memfn>, rvalue_noexcept_memfn>);
    CHECK(std::is_same_v<remove_const_t<rvalue_cv_memfn>, rvalue_volatile_memfn>);
    CHECK(std::is_same_v<remove_const_t<rvalue_noexcept_cv_memfn>, rvalue_noexcept_volatile_memfn>);

    CHECK(std::is_same_v<remove_const_t<rvalue_memfn>, rvalue_memfn>);
    CHECK(std::is_same_v<remove_const_t<rvalue_noexcept_memfn>, rvalue_noexcept_memfn>);
    CHECK(std::is_same_v<remove_const_t<rvalue_volatile_memfn>, rvalue_volatile_memfn>);
    CHECK(std::is_same_v<remove_const_t<rvalue_noexcept_volatile_memfn>,
                         rvalue_noexcept_volatile_memfn>);
  }
}

TEST_CASE("is_const should indicate if a member is const qualified") {
  CHECK(is_const_v<const_memfn>);
  CHECK(is_const_v<cv_memfn>);
  CHECK(is_const_v<noexcept_cv_memfn>);
  CHECK(is_const_v<lvalue_const_memfn>);
  CHECK(is_const_v<lvalue_cv_memfn>);
  CHECK(is_const_v<lvalue_noexcept_cv_memfn>);
  CHECK(is_const_v<rvalue_const_memfn>);
  CHECK(is_const_v<rvalue_cv_memfn>);
  CHECK(is_const_v<rvalue_noexcept_cv_memfn>);

  CHECK_FALSE(is_const_v<memfn>);
  CHECK_FALSE(is_const_v<volatile_memfn>);
  CHECK_FALSE(is_const_v<noexcept_memfn>);
  CHECK_FALSE(is_const_v<noexcept_volatile_memfn>);
  CHECK_FALSE(is_const_v<lvalue_memfn>);
  CHECK_FALSE(is_const_v<lvalue_volatile_memfn>);
  CHECK_FALSE(is_const_v<lvalue_noexcept_memfn>);
  CHECK_FALSE(is_const_v<lvalue_noexcept_volatile_memfn>);
  CHECK_FALSE(is_const_v<rvalue_memfn>);
  CHECK_FALSE(is_const_v<rvalue_volatile_memfn>);
  CHECK_FALSE(is_const_v<rvalue_noexcept_memfn>);
  CHECK_FALSE(is_const_v<rvalue_noexcept_volatile_memfn>);
}
