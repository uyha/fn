//
// Copyright (c) 2020-2020 Uy Ha (hchanuy at gmail dot com)
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
#ifndef RIVER_FN
#define RIVER_FN

#include <type_traits>

namespace river {
template <typename... Ts>
struct type_list {};
template <template <typename...> class... Ts>
struct higher_order_type_list {};

// region fn_trait
template <typename T>
struct fn_trait;
template <typename R, typename... Args>
struct fn_trait<R (*)(Args...)> {
  static constexpr bool is_free_fn    = true;
  static constexpr bool is_member_fn  = false;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using arguments   = type_list<Args...>;
};
template <typename R, typename... Args>
struct fn_trait<R (*)(Args...) noexcept> {
  static constexpr bool is_free_fn    = true;
  static constexpr bool is_member_fn  = false;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T>
struct fn_trait<R(T::*)> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = false;
  static constexpr bool is_member_ptr = true;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...)> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) volatile> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const volatile> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) volatile noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const volatile noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) &> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = true;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const &> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = true;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) volatile &> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = true;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const volatile &> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = true;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) &noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = true;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const &noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = true;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) volatile &noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = true;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const volatile &noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = true;
  static constexpr bool is_rvalue_ref = false;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) &&> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = true;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const &&> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = true;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) volatile &&> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = true;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const volatile &&> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = true;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = false;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) &&noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = true;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const &&noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = true;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = false;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) volatile &&noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = true;
  static constexpr bool is_const      = false;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
template <typename R, typename T, typename... Args>
struct fn_trait<R (T::*)(Args...) const volatile &&noexcept> {
  static constexpr bool is_free_fn    = false;
  static constexpr bool is_member_fn  = true;
  static constexpr bool is_member_ptr = false;
  static constexpr bool is_lvalue_ref = false;
  static constexpr bool is_rvalue_ref = true;
  static constexpr bool is_const      = true;
  static constexpr bool is_volatile   = true;
  static constexpr bool is_noexcept   = true;

  using return_type = R;
  using object_type = T;
  using arguments   = type_list<Args...>;
};
// endregion

namespace detail {
template <typename T>
constexpr T &&forward(typename std::remove_reference<T>::type &t) noexcept {
  return static_cast<T &&>(t);
}
template <typename T>
constexpr T &&forward(typename std::remove_reference<T>::type &&t) noexcept {
  static_assert(!std::is_lvalue_reference_v<T>);
  return static_cast<T &&>(t);
}

template <typename T>
using lvalue_ref_t = typename fn_trait<T>::object_type &;
template <typename T>
using const_lvalue_ref_t = typename fn_trait<T>::object_type const &;
template <typename T>
using volatile_lvalue_ref_t = typename fn_trait<T>::object_type volatile &;
template <typename T>
using cv_lvalue_ref_t = typename fn_trait<T>::object_type const volatile &;
template <typename T>
using rvalue_ref_t = typename fn_trait<T>::object_type &&;
template <typename T>
using const_rvalue_ref_t = typename fn_trait<T>::object_type const &&;
template <typename T>
using volatile_rvalue_ref_t = typename fn_trait<T>::object_type volatile &&;
template <typename T>
using cv_rvalue_ref_t = typename fn_trait<T>::object_type const volatile &&;

template <typename T>
struct simple_mapper {
private:
  static constexpr auto is_const    = fn_trait<T>::is_const;
  static constexpr auto is_volatile = fn_trait<T>::is_volatile;
  static const auto is_rvalue_ref   = fn_trait<T>::is_rvalue_ref;

  using object_type = typename fn_trait<T>::object_type;

public:
  using type = std::conditional_t<
      is_const && is_volatile,
      std::conditional_t<is_rvalue_ref, object_type const volatile &&, object_type const volatile &>,
      std::conditional_t<
          is_volatile,
          std::conditional_t<is_rvalue_ref, object_type volatile &&, object_type volatile &>,
          std::conditional_t<is_const,
                             std::conditional_t<is_rvalue_ref, object_type const &&, object_type const &>,
                             std::conditional_t<is_rvalue_ref, object_type &&, object_type &>>>>;
};
template <typename T>
using simple_mapper_t = typename simple_mapper<T>::type;

template <typename T, bool is_free_fn = fn_trait<T>::is_free_fn, bool is_member_ptr = fn_trait<T>::is_member_ptr>
struct overloading_mappers;
template <typename T>
struct overloading_mappers<T, true, false> {
  using type = type_list<>;
};
template <typename T>
struct overloading_mappers<T, false, false> {
private:
  static constexpr auto is_const    = fn_trait<T>::is_const;
  static constexpr auto is_volatile = fn_trait<T>::is_volatile;
  static const auto is_rvalue_ref   = fn_trait<T>::is_rvalue_ref;
  static const auto is_lvalue_ref   = fn_trait<T>::is_lvalue_ref;

public:
  using type = std::conditional_t<
      is_const && is_volatile,
      std::conditional_t<is_rvalue_ref,
                         higher_order_type_list<cv_rvalue_ref_t>,
                         std::conditional_t<is_lvalue_ref,
                                            higher_order_type_list<cv_lvalue_ref_t>,
                                            higher_order_type_list<cv_lvalue_ref_t, cv_rvalue_ref_t>>>,
      std::conditional_t<
          is_volatile,
          std::conditional_t<is_rvalue_ref,
                             higher_order_type_list<volatile_rvalue_ref_t>,
                             std::conditional_t<is_lvalue_ref,
                                                higher_order_type_list<volatile_lvalue_ref_t>,
                                                higher_order_type_list<volatile_lvalue_ref_t, volatile_rvalue_ref_t>>>,
          std::conditional_t<
              is_const,
              std::conditional_t<is_rvalue_ref,
                                 higher_order_type_list<const_rvalue_ref_t>,
                                 std::conditional_t<is_lvalue_ref,
                                                    higher_order_type_list<const_lvalue_ref_t>,
                                                    higher_order_type_list<const_lvalue_ref_t, const_rvalue_ref_t>>>,
              std::conditional_t<is_rvalue_ref,
                                 higher_order_type_list<rvalue_ref_t>,
                                 std::conditional_t<is_lvalue_ref,
                                                    higher_order_type_list<lvalue_ref_t>,
                                                    higher_order_type_list<lvalue_ref_t, rvalue_ref_t>>>>>>;
};
template <typename T>
struct overloading_mappers<T, false, true> {
  using type = higher_order_type_list<lvalue_ref_t,
                                      const_lvalue_ref_t,
                                      volatile_lvalue_ref_t,
                                      cv_lvalue_ref_t,
                                      rvalue_ref_t,
                                      const_rvalue_ref_t,
                                      volatile_rvalue_ref_t,
                                      cv_rvalue_ref_t>;
};

template <typename T>
using overloading_mappers_t = typename overloading_mappers<T>::type;

template <typename T,
          T fn,
          template <typename>
          class mapper,
          bool is_free_fn    = fn_trait<T>::is_free_fn,
          bool is_member_ptr = fn_trait<T>::is_member_ptr,
          typename Args      = typename fn_trait<T>::arguments>
struct SingleFnImpl;
template <typename T, T fn, typename... Args>
struct SingleFnImpl<T, fn, /*dummy*/ simple_mapper_t, true, false, type_list<Args...>> {
  constexpr auto operator()(Args... args) const noexcept(fn_trait<T>::is_noexcept) -> decltype(auto) {
    return fn(detail::forward<Args>(args)...);
  }
};
template <typename T, T fn, template <typename> class object_mapper_t, typename... Args>
struct SingleFnImpl<T, fn, object_mapper_t, false, false, type_list<Args...>> {
  constexpr auto operator()(object_mapper_t<T> object, Args... args) const noexcept(fn_trait<T>::is_noexcept)
      -> decltype(auto) {
    return (detail::forward<decltype(object)>(object).*fn)(detail::forward<Args>(args)...);
  }
};
template <typename T, T fn, template <typename> class object_mapper_t>
struct SingleFnImpl<T, fn, object_mapper_t, false, true, type_list<>> {
  constexpr auto operator()(object_mapper_t<T> object) const noexcept -> decltype(auto) {
    return object.*fn;
  }
};

template <typename T,
          T fn,
          typename mappers   = overloading_mappers_t<T>,
          bool is_free_fn    = fn_trait<T>::is_free_fn,
          bool is_member_ptr = fn_trait<T>::is_member_ptr,
          typename Args      = typename fn_trait<T>::arguments>
struct OverloadingFnImpl;
template <typename T, T fn, typename... Args>
struct OverloadingFnImpl<T, fn, type_list<>, true, false, type_list<Args...>>
    : SingleFnImpl<T, fn, /*dummy*/ simple_mapper_t, true, false, type_list<Args...>> {
  using SingleFnImpl<T, fn, simple_mapper_t, true, false, type_list<Args...>>::operator();
};
template <typename T, T fn, template <typename> class... mappers, typename... Args>
struct OverloadingFnImpl<T, fn, higher_order_type_list<mappers...>, false, false, type_list<Args...>>
    : SingleFnImpl<T, fn, mappers, false, false, type_list<Args...>>... {
  using SingleFnImpl<T, fn, mappers, false, false, type_list<Args...>>::operator()...;
};
template <typename T, T fn, template <typename> class... mappers>
struct OverloadingFnImpl<T, fn, higher_order_type_list<mappers...>, false, true, type_list<>>
    : SingleFnImpl<T, fn, mappers, false, true, type_list<>>... {
  using SingleFnImpl<T, fn, mappers, false, true, type_list<>>::operator()...;
};

} // namespace detail
template <auto f>
struct fn : detail::SingleFnImpl<decltype(f), f, detail::simple_mapper_t> {
  using detail::SingleFnImpl<decltype(f), f, detail::simple_mapper_t>::operator();
};
template <auto f>
struct overloading_fn : detail::OverloadingFnImpl<decltype(f), f> {
  using detail::OverloadingFnImpl<decltype(f), f>::operator();
};
template <auto f>
struct fn_trait<fn<f>> : fn_trait<decltype(f)> {};
template <auto f>
struct fn_trait<overloading_fn<f>> : fn_trait<decltype(f)> {};
template <auto f>
using fn_trait_of = fn_trait<std::remove_cv_t<decltype(f)>>;
} // namespace river
#endif