# Function pointers as lambda
![C/C++ CI](https://github.com/uyha/fn/workflows/C/C++%20CI/badge.svg)

This library provides a thin wrapper that turns (member) function pointers into individual types. It is intended make 
(member) function pointers behave like lambda but provide a more convenient syntax for it.

## Quickstart
```cpp
#include <fn/fn.hpp>

void function(){}

struct A{
   int function(){}; 
};

int main(){
    auto func = fn::fn<&function>{};
    func();
    
    auto mem_func = fn::fn<&A::function>{};
    mem_func(A{});
}
```

## Usage
This is a header only library, just copy `fn.hpp` to your project and start using it.
