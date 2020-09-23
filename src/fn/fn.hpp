//
// Created by uyha on 22.09.2020.
//

#pragma once

namespace fn {
namespace detail {
template <typename T>
struct remove_reference {
  using type = T;
};
template <typename T>
struct remove_reference<T &> {
  using type = T;
};
template <typename T>
struct remove_reference<T &&> {
  using type = T;
};

template <typename T>
struct is_lvalue_reference {
  static constexpr bool value = false;
};
template <typename T>
struct is_lvalue_reference<T &> {
  static constexpr bool value = true;
};

template <typename T>
constexpr T &&forward(typename remove_reference<T>::type &t) noexcept {
  return static_cast<T &&>(t);
}
template <typename T>
constexpr T &&forward(typename remove_reference<T>::type &&t) noexcept {
  static_assert(!is_lvalue_reference<T>::value);
  return static_cast<T &&>(t);
}
} // namespace detail

template <auto fp>
struct fn {
  template <typename... Args>
  constexpr auto operator()(Args &&... args) const
      noexcept(noexcept(fp(detail::forward<Args>(args)...)))
          -> decltype(fp(detail::forward<Args>(args)...)) {
    return fp(detail::forward<Args>(args)...);
  }
  template <typename T, typename... Args>
  constexpr auto operator()(T &&t, Args &&... args) const
      noexcept(noexcept((detail::forward<T>(t).*fp)(detail::forward<Args>(args)...)))
          -> decltype((detail::forward<T>(t).*fp)(detail::forward<Args>(args)...)) {
    return (detail::forward<T>(t).*fp)(detail::forward<Args>(args)...);
  }
};
} // namespace fn