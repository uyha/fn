//
// Created by uyha on 26.09.2020.
//
#include "common.hpp"

#include <catch2/catch.hpp>
#include <river/fn.hpp>

using namespace river;

template <typename...>
struct print_type;

TEST_CASE("fn_trait should return a type that contains the correct information about the (member) "
          "function type") {
  CHECK(fn_trait<normal_fn_ptr>::is_free_fn);
  CHECK_FALSE(fn_trait<normal_fn_ptr>::is_member_fn);
  CHECK_FALSE(fn_trait<normal_fn_ptr>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<normal_fn_ptr>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<normal_fn_ptr>::arguments, type_list<int>>);

  CHECK(fn_trait<noexcept_fn_ptr>::is_free_fn);
  CHECK_FALSE(fn_trait<noexcept_fn_ptr>::is_member_fn);
  CHECK(fn_trait<noexcept_fn_ptr>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<noexcept_fn_ptr>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<noexcept_fn_ptr>::arguments, type_list<int, long>>);

  CHECK_FALSE(fn_trait<memfn>::is_free_fn);
  CHECK(fn_trait<memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<memfn>::is_const);
  CHECK_FALSE(fn_trait<memfn>::is_volatile);
  CHECK_FALSE(fn_trait<memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<const_memfn>::is_free_fn);
  CHECK(fn_trait<const_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<const_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<const_memfn>::is_rvalue_ref);
  CHECK(fn_trait<const_memfn>::is_const);
  CHECK_FALSE(fn_trait<const_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<const_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<const_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<const_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<const_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<volatile_memfn>::is_free_fn);
  CHECK(fn_trait<volatile_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<volatile_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<volatile_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<volatile_memfn>::is_const);
  CHECK(fn_trait<volatile_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<volatile_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<volatile_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<volatile_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<volatile_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<cv_memfn>::is_free_fn);
  CHECK(fn_trait<cv_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<cv_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<cv_memfn>::is_rvalue_ref);
  CHECK(fn_trait<cv_memfn>::is_const);
  CHECK(fn_trait<cv_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<cv_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<cv_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<cv_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<cv_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<noexcept_memfn>::is_free_fn);
  CHECK(fn_trait<noexcept_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<noexcept_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<noexcept_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<noexcept_memfn>::is_const);
  CHECK_FALSE(fn_trait<noexcept_memfn>::is_volatile);
  CHECK(fn_trait<noexcept_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<noexcept_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<noexcept_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<noexcept_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<noexcept_const_memfn>::is_free_fn);
  CHECK(fn_trait<noexcept_const_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<noexcept_const_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<noexcept_const_memfn>::is_rvalue_ref);
  CHECK(fn_trait<noexcept_const_memfn>::is_const);
  CHECK_FALSE(fn_trait<noexcept_const_memfn>::is_volatile);
  CHECK(fn_trait<noexcept_const_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<noexcept_const_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<noexcept_const_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<noexcept_const_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<noexcept_volatile_memfn>::is_free_fn);
  CHECK(fn_trait<noexcept_volatile_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<noexcept_volatile_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<noexcept_volatile_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<noexcept_volatile_memfn>::is_const);
  CHECK(fn_trait<noexcept_volatile_memfn>::is_volatile);
  CHECK(fn_trait<noexcept_volatile_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<noexcept_volatile_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<noexcept_volatile_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<noexcept_volatile_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<noexcept_cv_memfn>::is_free_fn);
  CHECK(fn_trait<noexcept_cv_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<noexcept_cv_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<noexcept_cv_memfn>::is_rvalue_ref);
  CHECK(fn_trait<noexcept_cv_memfn>::is_const);
  CHECK(fn_trait<noexcept_cv_memfn>::is_volatile);
  CHECK(fn_trait<noexcept_cv_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<noexcept_cv_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<noexcept_cv_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<noexcept_cv_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<lvalue_memfn>::is_free_fn);
  CHECK(fn_trait<lvalue_memfn>::is_member_fn);
  CHECK(fn_trait<lvalue_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_memfn>::is_const);
  CHECK_FALSE(fn_trait<lvalue_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<lvalue_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<lvalue_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<lvalue_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<lvalue_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<lvalue_const_memfn>::is_free_fn);
  CHECK(fn_trait<lvalue_const_memfn>::is_member_fn);
  CHECK(fn_trait<lvalue_const_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_const_memfn>::is_rvalue_ref);
  CHECK(fn_trait<lvalue_const_memfn>::is_const);
  CHECK_FALSE(fn_trait<lvalue_const_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<lvalue_const_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<lvalue_const_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<lvalue_const_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<lvalue_const_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<lvalue_volatile_memfn>::is_free_fn);
  CHECK(fn_trait<lvalue_volatile_memfn>::is_member_fn);
  CHECK(fn_trait<lvalue_volatile_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_volatile_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_volatile_memfn>::is_const);
  CHECK(fn_trait<lvalue_volatile_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<lvalue_volatile_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<lvalue_volatile_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<lvalue_volatile_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<lvalue_volatile_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<lvalue_cv_memfn>::is_free_fn);
  CHECK(fn_trait<lvalue_cv_memfn>::is_member_fn);
  CHECK(fn_trait<lvalue_cv_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_cv_memfn>::is_rvalue_ref);
  CHECK(fn_trait<lvalue_cv_memfn>::is_const);
  CHECK(fn_trait<lvalue_cv_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<lvalue_cv_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<lvalue_cv_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<lvalue_cv_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<lvalue_cv_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<lvalue_noexcept_memfn>::is_free_fn);
  CHECK(fn_trait<lvalue_noexcept_memfn>::is_member_fn);
  CHECK(fn_trait<lvalue_noexcept_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_noexcept_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_noexcept_memfn>::is_const);
  CHECK_FALSE(fn_trait<lvalue_noexcept_memfn>::is_volatile);
  CHECK(fn_trait<lvalue_noexcept_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<lvalue_noexcept_const_memfn>::is_free_fn);
  CHECK(fn_trait<lvalue_noexcept_const_memfn>::is_member_fn);
  CHECK(fn_trait<lvalue_noexcept_const_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_noexcept_const_memfn>::is_rvalue_ref);
  CHECK(fn_trait<lvalue_noexcept_const_memfn>::is_const);
  CHECK_FALSE(fn_trait<lvalue_noexcept_const_memfn>::is_volatile);
  CHECK(fn_trait<lvalue_noexcept_const_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_const_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_const_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_const_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<lvalue_noexcept_volatile_memfn>::is_free_fn);
  CHECK(fn_trait<lvalue_noexcept_volatile_memfn>::is_member_fn);
  CHECK(fn_trait<lvalue_noexcept_volatile_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_noexcept_volatile_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_noexcept_volatile_memfn>::is_const);
  CHECK(fn_trait<lvalue_noexcept_volatile_memfn>::is_volatile);
  CHECK(fn_trait<lvalue_noexcept_volatile_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_volatile_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_volatile_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_volatile_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<lvalue_noexcept_cv_memfn>::is_free_fn);
  CHECK(fn_trait<lvalue_noexcept_cv_memfn>::is_member_fn);
  CHECK(fn_trait<lvalue_noexcept_cv_memfn>::is_lvalue_ref);
  CHECK_FALSE(fn_trait<lvalue_noexcept_cv_memfn>::is_rvalue_ref);
  CHECK(fn_trait<lvalue_noexcept_cv_memfn>::is_const);
  CHECK(fn_trait<lvalue_noexcept_cv_memfn>::is_volatile);
  CHECK(fn_trait<lvalue_noexcept_cv_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_cv_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_cv_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<lvalue_noexcept_cv_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<rvalue_memfn>::is_free_fn);
  CHECK(fn_trait<rvalue_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<rvalue_memfn>::is_lvalue_ref);
  CHECK(fn_trait<rvalue_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<rvalue_memfn>::is_const);
  CHECK_FALSE(fn_trait<rvalue_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<rvalue_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<rvalue_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<rvalue_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<rvalue_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<rvalue_const_memfn>::is_free_fn);
  CHECK(fn_trait<rvalue_const_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<rvalue_const_memfn>::is_lvalue_ref);
  CHECK(fn_trait<rvalue_const_memfn>::is_rvalue_ref);
  CHECK(fn_trait<rvalue_const_memfn>::is_const);
  CHECK_FALSE(fn_trait<rvalue_const_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<rvalue_const_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<rvalue_const_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<rvalue_const_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<rvalue_const_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<rvalue_volatile_memfn>::is_free_fn);
  CHECK(fn_trait<rvalue_volatile_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<rvalue_volatile_memfn>::is_lvalue_ref);
  CHECK(fn_trait<rvalue_volatile_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<rvalue_volatile_memfn>::is_const);
  CHECK(fn_trait<rvalue_volatile_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<rvalue_volatile_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<rvalue_volatile_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<rvalue_volatile_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<rvalue_volatile_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<rvalue_cv_memfn>::is_free_fn);
  CHECK(fn_trait<rvalue_cv_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<rvalue_cv_memfn>::is_lvalue_ref);
  CHECK(fn_trait<rvalue_cv_memfn>::is_rvalue_ref);
  CHECK(fn_trait<rvalue_cv_memfn>::is_const);
  CHECK(fn_trait<rvalue_cv_memfn>::is_volatile);
  CHECK_FALSE(fn_trait<rvalue_cv_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<rvalue_cv_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<rvalue_cv_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<rvalue_cv_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<rvalue_noexcept_memfn>::is_free_fn);
  CHECK(fn_trait<rvalue_noexcept_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<rvalue_noexcept_memfn>::is_lvalue_ref);
  CHECK(fn_trait<rvalue_noexcept_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<rvalue_noexcept_memfn>::is_const);
  CHECK_FALSE(fn_trait<rvalue_noexcept_memfn>::is_volatile);
  CHECK(fn_trait<rvalue_noexcept_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<rvalue_noexcept_const_memfn>::is_free_fn);
  CHECK(fn_trait<rvalue_noexcept_const_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<rvalue_noexcept_const_memfn>::is_lvalue_ref);
  CHECK(fn_trait<rvalue_noexcept_const_memfn>::is_rvalue_ref);
  CHECK(fn_trait<rvalue_noexcept_const_memfn>::is_const);
  CHECK_FALSE(fn_trait<rvalue_noexcept_const_memfn>::is_volatile);
  CHECK(fn_trait<rvalue_noexcept_const_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_const_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_const_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_const_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<rvalue_noexcept_volatile_memfn>::is_free_fn);
  CHECK(fn_trait<rvalue_noexcept_volatile_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<rvalue_noexcept_volatile_memfn>::is_lvalue_ref);
  CHECK(fn_trait<rvalue_noexcept_volatile_memfn>::is_rvalue_ref);
  CHECK_FALSE(fn_trait<rvalue_noexcept_volatile_memfn>::is_const);
  CHECK(fn_trait<rvalue_noexcept_volatile_memfn>::is_volatile);
  CHECK(fn_trait<rvalue_noexcept_volatile_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_volatile_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_volatile_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_volatile_memfn>::arguments, type_list<>>);

  CHECK_FALSE(fn_trait<rvalue_noexcept_cv_memfn>::is_free_fn);
  CHECK(fn_trait<rvalue_noexcept_cv_memfn>::is_member_fn);
  CHECK_FALSE(fn_trait<rvalue_noexcept_cv_memfn>::is_lvalue_ref);
  CHECK(fn_trait<rvalue_noexcept_cv_memfn>::is_rvalue_ref);
  CHECK(fn_trait<rvalue_noexcept_cv_memfn>::is_const);
  CHECK(fn_trait<rvalue_noexcept_cv_memfn>::is_volatile);
  CHECK(fn_trait<rvalue_noexcept_cv_memfn>::is_noexcept);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_cv_memfn>::return_type, int>);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_cv_memfn>::object_type, A>);
  CHECK(std::is_same_v<fn_trait<rvalue_noexcept_cv_memfn>::arguments, type_list<>>);
}

TEST_CASE("fn_trait on `fn` and `overloading_fn` gives the trait on their underlying function pointer") {
  CHECK(std::is_base_of_v<fn_trait<noexcept_fn_ptr>, fn_trait<fn<&fn_noexcept>>>);
  CHECK(std::is_base_of_v<fn_trait<rvalue_noexcept_cv_memfn>, fn_trait<fn<&A::rvalue_fn_const_volatile_noexcept>>>);
}
