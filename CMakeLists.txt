cmake_minimum_required(VERSION 3.12)
project("fn"
        VERSION 0.2
        # There is a bug in conan.cmake that make libraries fail to build if LANGUAGES is specified with only CXX
        LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(river
                     GIT_REPOSITORY https://github.com/uyha/cmake-modules.git
                     GIT_TAG v0.1.0)
FetchContent_MakeAvailable(river)
list(APPEND CMAKE_MODULE_PATH "${river_SOURCE_DIR}")

add_subdirectory(examples)
add_subdirectory(src)
add_subdirectory(tests)

if (FN_INCLUDE_BENCHMARKS)
    add_subdirectory(benchmarks)
endif ()
