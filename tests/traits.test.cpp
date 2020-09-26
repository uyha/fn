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

TEST_CASE("remove_noexcept should return the same signature with no noexcept specifier") {
  CHECK(std::is_same_v<remove_noexcept_t<noexcept_fn>, normal_fn>);
  CHECK(std::is_same_v<remove_noexcept_t<noexcept_fn_ptr>, normal_fn_ptr>);
  CHECK(std::is_same_v<remove_noexcept_t<noexcept_memfn>, memfn>);
  CHECK(std::is_same_v<remove_noexcept_t<noexcept_const_memfn>, const_memfn>);
  CHECK(std::is_same_v<remove_noexcept_t<noexcept_volatile_memfn>, volatile_memfn>);
  CHECK(std::is_same_v<remove_noexcept_t<noexcept_cv_memfn>, cv_memfn>);
}

TEST_CASE("remove_const should return the same signature with no const specifier") {}

TEST_CASE("is_noexcept trait should return true for noexcept functions and false otherwise") {
  CHECK_FALSE(is_noexcept_v<normal_fn>);
  CHECK_FALSE(is_noexcept_v<normal_fn_ptr>);
  CHECK_FALSE(is_noexcept_v<memfn>);
  CHECK_FALSE(is_noexcept_v<const_memfn>);
  CHECK_FALSE(is_noexcept_v<volatile_memfn>);
  CHECK_FALSE(is_noexcept_v<cv_memfn>);

  CHECK(is_noexcept_v<noexcept_fn>);
  CHECK(is_noexcept_v<noexcept_fn_ptr>);
  CHECK(is_noexcept_v<noexcept_memfn>);
  CHECK(is_noexcept_v<noexcept_const_memfn>);
  CHECK(is_noexcept_v<noexcept_volatile_memfn>);
  CHECK(is_noexcept_v<noexcept_cv_memfn>);
}

TEST_CASE("is_const_member_function should return true for const member functions") {
  CHECK(is_const_member_function_v<void (A::*)() const>);
  CHECK(is_const_member_function_v<void (A::*)() const volatile>);
}