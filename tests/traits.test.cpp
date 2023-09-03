//
// Created by uyha on 26.09.2020.
//
#include "common.hpp"

#include <catch2/catch_test_macros.hpp>
#include <river/fn.hpp>

using namespace river;

template <typename...>
struct print_type;

TEST_CASE("fn_trait should return a type that contains the correct information about the (member) "
          "function type") {
  STATIC_CHECK(fn_trait<normal_fn_ptr>::type == FnType::free_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<normal_fn_ptr>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<normal_fn_ptr>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<normal_fn_ptr>::arguments, type_list<int>>);

  STATIC_CHECK(fn_trait<noexcept_fn_ptr>::type == FnType::free_fn_ptr);
  STATIC_CHECK(fn_trait<noexcept_fn_ptr>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_fn_ptr>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_fn_ptr>::arguments, type_list<int, long>>);

  STATIC_CHECK(fn_trait<memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(std::is_same_v<fn_trait<memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<memfn>::object_t, A>);
  STATIC_CHECK(std::is_same_v<fn_trait<memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<const_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(std::is_same_v<fn_trait<const_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<const_memfn>::object_t, A const>);
  STATIC_CHECK(std::is_same_v<fn_trait<const_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<volatile_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<volatile_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<volatile_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<volatile_memfn>::object_t, A volatile>);
  STATIC_CHECK(std::is_same_v<fn_trait<volatile_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<cv_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<cv_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<cv_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<cv_memfn>::object_t, A const volatile>);
  STATIC_CHECK(std::is_same_v<fn_trait<cv_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<noexcept_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<noexcept_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_memfn>::object_t, A>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<noexcept_const_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<noexcept_const_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_const_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_const_memfn>::object_t, A const>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_const_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<noexcept_volatile_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<noexcept_volatile_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_volatile_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_volatile_memfn>::object_t, A volatile>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_volatile_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<noexcept_cv_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<noexcept_cv_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_cv_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_cv_memfn>::object_t, A const volatile>);
  STATIC_CHECK(std::is_same_v<fn_trait<noexcept_cv_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<lvalue_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<lvalue_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_memfn>::object_t, A &>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<lvalue_const_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<lvalue_const_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_const_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_const_memfn>::object_t, A const &>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_const_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<lvalue_volatile_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<lvalue_volatile_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_volatile_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_volatile_memfn>::object_t, A volatile &>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_volatile_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<lvalue_cv_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<lvalue_cv_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_cv_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_cv_memfn>::object_t, A const volatile &>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_cv_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<lvalue_noexcept_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<lvalue_noexcept_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_memfn>::object_t, A &>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<lvalue_noexcept_const_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<lvalue_noexcept_const_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_const_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_const_memfn>::object_t, A const &>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_const_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<lvalue_noexcept_volatile_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<lvalue_noexcept_volatile_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_volatile_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_volatile_memfn>::object_t, A volatile &>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_volatile_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<lvalue_noexcept_cv_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<lvalue_noexcept_cv_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_cv_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_cv_memfn>::object_t, A const volatile &>);
  STATIC_CHECK(std::is_same_v<fn_trait<lvalue_noexcept_cv_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<rvalue_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<rvalue_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_memfn>::object_t, A &&>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<rvalue_const_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<rvalue_const_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_const_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_const_memfn>::object_t, A const &&>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_const_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<rvalue_volatile_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<rvalue_volatile_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_volatile_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_volatile_memfn>::object_t, A volatile &&>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_volatile_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<rvalue_cv_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK_FALSE(fn_trait<rvalue_cv_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_cv_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_cv_memfn>::object_t, A const volatile &&>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_cv_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<rvalue_noexcept_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<rvalue_noexcept_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_memfn>::object_t, A &&>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<rvalue_noexcept_const_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<rvalue_noexcept_const_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_const_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_const_memfn>::object_t, A const &&>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_const_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<rvalue_noexcept_volatile_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<rvalue_noexcept_volatile_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_volatile_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_volatile_memfn>::object_t, A volatile &&>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_volatile_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<rvalue_noexcept_cv_memfn>::type == FnType::member_fn_ptr);
  STATIC_CHECK(fn_trait<rvalue_noexcept_cv_memfn>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_cv_memfn>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_cv_memfn>::object_t, A const volatile &&>);
  STATIC_CHECK(std::is_same_v<fn_trait<rvalue_noexcept_cv_memfn>::arguments, type_list<>>);

  STATIC_CHECK(fn_trait<Invocable>::type == FnType::invocable);
  STATIC_CHECK_FALSE(fn_trait<Invocable>::is_noexcept);
  STATIC_CHECK(std::is_same_v<fn_trait<Invocable>::return_t, int>);
  STATIC_CHECK(std::is_same_v<fn_trait<Invocable>::object_t, Invocable>);
  STATIC_CHECK(std::is_same_v<fn_trait<Invocable>::arguments, type_list<>>);
}
