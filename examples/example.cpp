#include <cassert>
#include <river/fn.hpp>

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