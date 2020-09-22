# A template for C++ projects
![C/C++ CI](https://github.com/uyha/cpp_template/workflows/C/C++%20CI/badge.svg)

This is a template to start a new C++ project with dependency management built
 into it. Hence, it is opinionated about how dependency management of a C++ 
 project can be done. This template uses `conan` to manage C++'s dependency. In
 addition to that, if Python is needed for the project, it also uses `pipenv` to
 manage Python's virtual environments and its dependencies.

## Requirements
* `cmake`
* `conan`

## Usage
Just clone/download the project or click the [Use this template](https://github.com/uyha/cpp_template/generate)
 button if you're using Github as your git hosting site and start coding.

Users are encouraged to learn a bit about how [conan](https://docs.conan.io/en/latest/getting_started.html)
 works to better understand the `conanfile.txt` and how to add more
 dependencies.

### Miscellaneous
To opt out of using `pipenv` for finding `conan`, delete the Pipfile at the
 project's root.
 
Provide `Python_ROOT_DIR` if `conan` is installed using `pip` so `conan` can
 be found automatically.

[Pitchfork]: https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs
