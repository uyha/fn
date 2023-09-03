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

struct Callable {
  void operator()() const {}
};

int main() {
  static_assert(river::fn_trait_of<function>::type == river::FnType::free_fn_ptr);
  constexpr auto func = river::fn<function>;
  func();

  A a{};

  static_assert(river::fn_trait_of<&A::function>::type == river::FnType::member_fn_ptr);
  constexpr auto mem_func = river::fn<&A::function>;
  mem_func(a);

  static_assert(river::fn_trait_of<&A::a>::type == river::FnType::member_var_ptr);
  constexpr auto mem_var = river::fn<&A::a>;
  mem_var(a);

  static_assert(river::fn_trait<Callable>::type == river::FnType::invocable);
  constexpr auto callable = river::Fn{Callable{}};
  callable();

  A const b{};
  auto overloading_func = river::over_fn<&A::function>;
  overloading_func(a);
  overloading_func(A{});

  auto member = river::over_fn<&A::a>;
  assert(member(a) == 0);
  assert(member(b) == 0);
  assert(member(A{}) == 0);
}
```

## Usage

This is a header only library, just copy [fn.hpp](https://raw.githubusercontent.com/uyha/fn/master/src/river/fn.hpp) to
your project and start using it. This library requires C++17.

## Features

### `fn_trait`

This library provides the `fn_trait` class that provides details about:

- invocables (classes with an `operator()`, passing classes with an overload set of
  `operator()` will create a compile time error)
- free function pointers
- member function pointers
- member variable pointers

The following table shows the details provided by the `fn_trait`:

| Input                    | `type`                   | `is_noexcept` | `return_t` | `object_t` | `arguments`          |
| ------------------------ | ------------------------ | ------------- | ---------- | ---------- | -------------------- |
| Invocables               | `FnType::invocable`      | `bool`        | `R`        | `T`        | `type_list<Args...>` |
| Free function pointers   | `FnType::free_fn_ptr`    | `bool`        | `R`        | -          | `type_list<Args...>` |
| Member function pointers | `FnType::member_fn_ptr`  | `bool`        | `R`        | `T`        | `type_list<Args...>` |
| Member variable pointers | `FnType::member_var_ptr` | -             | `R`        | `T`        | `type_list<>`        |

`fn_trait<T>::arguments` is a `river::type_list`, in other to use this list, you
can have a function template that accepts `river::type_list` as normal parameter and
have the template parameters being a pack. The following snippet demonstrate this:

```cpp
template<typename... Args>
auto use_args(river::type_list<Args...>) {
  // do something with `Args`
}

// `Args` will be `int`, `bool`
use_args(river::fn_trait<void(*)(int, bool)>::arguments{});

// lambda
void unpack_with_lambda() {
  auto lambda = []<typename... Args>(river::type_list<Args...>) {
    //do something with `Args`
  };

  // `Args` will be `int`, `bool`
  lambda(river::fn_trait<void (*)(int, bool)>::arguments{});
}
```

This library was originally developed to provide a feature for constructing guards and
actions for [sml][sml] easily from free functions and member functions. The `fn` class
template is designed for that (although it fails to compile on MSVC when propagating
`noexcept`). `fn` provides just one `operator()` function that accepts a reasonable set
of arguments and not an overload set of it since **sml** fails to call the correct
function when there is an overload set. If you need an object that can be called with
all the possible valid arguments, then `overloading_fn` should be used instead.

If you want to create the function objects with runtime arguments, you can use `Fn` and
`OverFn`. They have the equivalent functionality with `fn`, and `over_fn`, but they
accept the function pointers/invocables as runtime parameters instead of compile time
parameters.

## Performance

This library incurs no overhead when `fn` and `overloading_fn` are used in `constexpr`
context and/or maximum optimization.

### Same TU function pointer

https://godbolt.org/z/E14P31dvK

```cpp
#include <river/fn.hpp>

int test(){
    return 42;
}

int main(){
    const auto f = river::fn<test>;
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

https://godbolt.org/z/s6rnr835M

```cpp
#include <river/fn.hpp>
int test();

int main(){
    const auto f = river::fn<test>;
    return f();
}
```

```asm
main:
        jmp     test()
```

[sml]: https://github.com/boost-ext/sml
