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

#pragma once
#ifndef FN_ENABLE_OVERLOAD
#define FN_ENABLE_OVERLOAD 1
#endif

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

template <typename T, T>
struct FnImpl;

// region Free functions
template <typename R, typename... Args, R (*fn)(Args...)>
struct FnImpl<decltype(fn), fn> {
  constexpr R operator()(Args &&... args) const {
    return fn(forward<Args>(args)...);
  }
};
template <typename R, typename... Args, R (*fn)(Args...) noexcept>
struct FnImpl<decltype(fn), fn> {
#ifdef _MSC_VER
  constexpr R operator()(Args &&... args) const {
    return fn(forward<Args>(args)...);
  }
#else
  constexpr R operator()(Args &&... args) const noexcept {
    return fn(forward<Args>(args)...);
  }
#endif
};
// endregion

// region Member functions
template <typename R, typename T, typename... Args, R (T::*fn)(Args...)>
struct FnImpl<decltype(fn), fn> {
  constexpr R operator()(T &obj, Args &&... args) const {
    return (obj.*fn)(forward<Args>(args)...);
  }
#if FN_ENABLE_OVERLOAD
  constexpr R operator()(T &&obj, Args &&... args) const {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
#endif
};
template <typename R, typename T, typename... Args, R (T::*fn)(Args...) const>
struct FnImpl<decltype(fn), fn> {
  constexpr R operator()(T const &obj, Args &&... args) const {
    return (obj.*fn)(forward<Args>(args)...);
  }
};
template <typename R, typename T, typename... Args, R (T::*fn)(Args...) noexcept>
struct FnImpl<decltype(fn), fn> {
#ifdef _MSC_VER
  constexpr R operator()(T &obj, Args &&... args) const {
    return (obj.*fn)(forward<Args>(args)...);
  }
#else
  constexpr R operator()(T &obj, Args &&... args) const noexcept {
    return (obj.*fn)(forward<Args>(args)...);
  }
#endif
#if FN_ENABLE_OVERLOAD
#ifdef _MSC_VER
  constexpr R operator()(T &&obj, Args &&... args) const {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
#else
  constexpr R operator()(T &&obj, Args &&... args) const noexcept {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
#endif
#endif
};
template <typename R, typename T, typename... Args, R (T::*fn)(Args...) const noexcept>
struct FnImpl<decltype(fn), fn> {
#ifdef _MSC_VER
  constexpr R operator()(T const &obj, Args &&... args) const {
    return (obj.*fn)(forward<Args>(args)...);
  }
#else
  constexpr R operator()(T const &obj, Args &&... args) const noexcept {
    return (obj.*fn)(forward<Args>(args)...);
  }
#endif
};
template <typename R, typename T, typename... Args, R (T::*fn)(Args...) &&>
struct FnImpl<decltype(fn), fn> {
  constexpr R operator()(T &&obj, Args &&... args) const {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
};
template <typename R, typename T, typename... Args, R (T::*fn)(Args...) const &&>
struct FnImpl<decltype(fn), fn> {
  constexpr R operator()(T const &&obj, Args &&... args) const {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
};
template <typename R, typename T, typename... Args, R (T::*fn)(Args...) &&noexcept>
struct FnImpl<decltype(fn), fn> {
#ifdef _MSC_VER
  constexpr R operator()(T &&obj, Args &&... args) const {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
#else
  constexpr R operator()(T &&obj, Args &&... args) const noexcept {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
#endif
};
template <typename R, typename T, typename... Args, R (T::*fn)(Args...) const &&noexcept>
struct FnImpl<decltype(fn), fn> {
#ifdef _MSC_VER
  constexpr R operator()(T const &&obj, Args &&... args) const {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
#else
  constexpr R operator()(T const &&obj, Args &&... args) const noexcept {
    return (forward<decltype(obj)>(obj).*fn)(forward<Args>(args)...);
  }
#endif
};
// endregion

} // namespace detail

template <auto fp>
using fn = detail::FnImpl<decltype(fp), fp>;
} // namespace fn