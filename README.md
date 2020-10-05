# Function pointers as lambda
![C/C++ CI](https://github.com/uyha/fn/workflows/C/C++%20CI/badge.svg)

This library provides a trait for querying information about a function pointer type, whether it is free function 
pointer, a member function pointer, noexcept, etc. It also provides a thin wrapper that turns (member) function 
pointers into individual types. It is intended make (member) function pointers behave like lambda but with a more 
convenient syntax.

## Quickstart
```cpp
#include <cassert>
#include <fn/fn.hpp>

void function() {}

struct A {
  void function(){};

  int a{0};
};

int main() {
  auto func = river::fn<&function>{};
  static_assert(river::fn_trait<decltype(&function)>::is_free_fn);
  func();

  auto mem_func = river::fn<&A::function>{};
  static_assert(river::fn_trait<decltype(&A::function)>::is_member_fn);
  A a{};
  mem_func(a);

  A const b{};
  auto overloading_func = river::overloading_fn<&A::function>{};
  overloading_func(a);
  overloading_func(A{});

  auto member = river::overloading_fn<&A::a>{};
  assert(member(a) == 0);
  assert(member(b) == 0);
  assert(member(A{}) == 0);
}
```

## Features
This library provides 1 trait and 2 wrapper classes. The trait `fn_trait` provides details about a (member) function 
pointer. For free function pointers, the following information is available:
- `is_free_fn`, `is_member_fn`, `is_member_ptr`, `is_noexcept`
- `return_type`
- `arguments`: The arguments are stored in the `type_list` type. To use it, create a template with a type template 
parameter, then specialize it with a type template parameter pack. 
```cpp
template<typename T>
struct get_args;
template<typename... Args>
struct get_args<type_list<Args...>>{};
```
For member function pointers or member variable pointers, in addition to the information for free function pointers, 
the following information is also available:
- `is_lvalue_ref`, `is_rvalue_ref`, `is_const`, `is_volatile`
- `object_type`

This library was originally developed to provide a feature for constructing guards and actions for [sml][sml] easily 
from free functions and member functions. The `fn` class template is designed for that (although it fails to compile 
on MSVC when propagating `noexcept`). `fn` provides just one `operator()` function that accepts a reasonable set of 
arguments and not an overload set of it since **sml** fails to call the correct function when there is a overload set.

If you need an object that can be called with all the possible valid arguments, then `overloading_fn` should be used 
instead.

## Usage
This is a header only library, just copy `fn.hpp` to your project and start using it.

[sml]: https://github.com/boost-ext/sml