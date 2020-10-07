//
// Created by uyha on 07.10.2020.
//

#pragma once
int fn1(int) {
  return 1;
}
int fn2(int) {
  return 1;
}

int fn_noexcept(int, long) noexcept {
  return 1;
}

using normal_fn_ptr   = int (*)(int);
using noexcept_fn_ptr = int (*)(int, long) noexcept;

struct A {
  int a;

  int fn() {
    return a;
  }
  int fn_const() const {
    return a;
  }
  int fn_volatile() volatile {
    return a;
  }
  int fn_const_volatile() const volatile {
    return a;
  }
  int fn_noexcept() noexcept {
    return a;
  }
  int fn_const_noexcept() const noexcept {
    return a;
  }
  int fn_volatile_noexcept() volatile noexcept {
    return a;
  }
  int fn_const_volatile_noexcept() const volatile noexcept {
    return a;
  }

  int lvalue_fn() & {
    return a;
  }
  int lvalue_fn_const() const & {
    return a;
  }
  int lvalue_fn_volatile() volatile & {
    return a;
  }
  int lvalue_fn_const_volatile() const volatile & {
    return a;
  }
  int lvalue_fn_noexcept() &noexcept {
    return a;
  }
  int lvalue_fn_const_noexcept() const &noexcept {
    return a;
  }
  int lvalue_fn_volatile_noexcept() volatile &noexcept {
    return a;
  }
  int lvalue_fn_const_volatile_noexcept() const volatile &noexcept {
    return a;
  }

  int rvalue_fn() && {
    return a;
  }
  int rvalue_fn_const() const && {
    return a;
  }
  int rvalue_fn_volatile() volatile && {
    return a;
  }
  int rvalue_fn_const_volatile() const volatile && {
    return a;
  }
  int rvalue_fn_noexcept() &&noexcept {
    return a;
  }
  int rvalue_fn_const_noexcept() const &&noexcept {
    return a;
  }
  int rvalue_fn_volatile_noexcept() volatile &&noexcept {
    return a;
  }
  int rvalue_fn_const_volatile_noexcept() const volatile &&noexcept {
    return a;
  }
};

using memfn                   = int (A::*)();
using const_memfn             = int (A::*)() const;
using volatile_memfn          = int (A::*)() volatile;
using cv_memfn                = int (A::*)() const volatile;
using noexcept_memfn          = int (A::*)() noexcept;
using noexcept_const_memfn    = int (A::*)() const noexcept;
using noexcept_volatile_memfn = int (A::*)() volatile noexcept;
using noexcept_cv_memfn       = int (A::*)() const volatile noexcept;

using lvalue_memfn                   = int (A::*)() &;
using lvalue_const_memfn             = int (A::*)() const &;
using lvalue_volatile_memfn          = int (A::*)() volatile &;
using lvalue_cv_memfn                = int (A::*)() const volatile &;
using lvalue_noexcept_memfn          = int (A::*)() &noexcept;
using lvalue_noexcept_const_memfn    = int (A::*)() const &noexcept;
using lvalue_noexcept_volatile_memfn = int (A::*)() volatile &noexcept;
using lvalue_noexcept_cv_memfn       = int (A::*)() const volatile &noexcept;

using rvalue_memfn                   = int (A::*)() &&;
using rvalue_const_memfn             = int (A::*)() const &&;
using rvalue_volatile_memfn          = int (A::*)() volatile &&;
using rvalue_cv_memfn                = int (A::*)() const volatile &&;
using rvalue_noexcept_memfn          = int (A::*)() &&noexcept;
using rvalue_noexcept_const_memfn    = int (A::*)() const &&noexcept;
using rvalue_noexcept_volatile_memfn = int (A::*)() volatile &&noexcept;
using rvalue_noexcept_cv_memfn       = int (A::*)() const volatile &&noexcept;
