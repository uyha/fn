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
