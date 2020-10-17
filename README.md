# Function pointers as lambda
![C/C++ CI](https://github.com/uyha/fn/workflows/C/C++%20CI/badge.svg)

This library provides a trait for querying information about a function pointer type, whether it is a free function 
pointer, a member function pointer, noexcept, etc. It also provides a thin wrapper that turns (member) function 
pointers into individual types. It is intended to make (member) function pointers behave like lambda but with a more 
convenient syntax. **C**'s variadic function pointers are not supported.

## Quickstart
```cpp
#include <cassert>
#include <river/fn.hpp>

void function() {}

struct A {
  void function(){};

  int a{0};
};

int main() {
  constexpr auto func = river::fn<function>{};
  static_assert(river::fn_trait_of<function>::is_free_fn);
  func();

  auto mem_func = river::fn<&A::function>{};
  static_assert(river::fn_trait_of<&A::function>::is_member_fn);
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
## Usage
This is a header only library, just copy [fn.hpp](https://raw.githubusercontent.com/uyha/fn/master/src/river/fn.hpp) to 
your project and start using it. This library requires C++17.

## Features
This library provides 1 trait and 2 wrapper classes. The trait `fn_trait` provides details about a (member) function 
pointer. For free function pointers, the following information is available:
- `is_free_fn`, `is_member_fn`, `is_member_ptr`, `is_noexcept`
- `return_type`
- `arguments`: The argument types are stored in the `type_list` type. To use it, create a template with a type template 
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
arguments and not an overload set of it since **sml** fails to call the correct function when there is an overload set.

If you need an object that can be called with all the possible valid arguments, then `overloading_fn` should be used 
instead.

## Performance
This library incurs no overhead when `fn` and `overloading_fn` are used in `constexpr` context and maximum optimization.

### Same TU function pointer

https://godbolt.org/z/M8xxh1
```cpp
#include <river/fn.hpp>

int test(){
    return 42;
}

int main(){
    const auto f = river::fn<test>{};
    return f();
}
```

```asm
test():
        mov     eax, 42
        ret
main:
        mov     eax, 42
        ret
```

### Different TU function pointer

https://godbolt.org/z/rf5zfE
```cpp
#include <river/fn.hpp>
int test();

int main(){
    const auto f = river::fn<test>{};
    return f();
}
```

```asm
main:
        jmp     test()
```
[sml]: https://github.com/boost-ext/sml