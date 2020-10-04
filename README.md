# Function pointers as lambda
![C/C++ CI](https://github.com/uyha/fn/workflows/C/C++%20CI/badge.svg)

This library provides a trait for querying information about a function pointer type, weather it is free function 
pointer, a member function pointer, noexcept, etc. It also provides a thin wrapper that turns (member) function 
pointers into individual types. It is intended make (member) function pointers behave like lambda but provide a more 
convenient syntax for it.

## Quickstart
```cpp
#include <fn/fn.hpp>

void function(){}

struct A{
   int function(){}; 
};

int main(){
    auto func = river::fn<&function>{};
    static_assert(river::fn_trait<&function>::is_free_fn);
    func();
    
    auto mem_func = river::fn<&A::function>{};
    static_assert(river::fn_trait<&A::function>::is_member_fn);
    A a{};
    mem_func(a);
}
```

## Usage
This is a header only library, just copy `fn.hpp` to your project and start using it.
