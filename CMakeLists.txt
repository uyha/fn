cmake_minimum_required(VERSION 3.12)
project("ProjectName"
        VERSION 0.0
        # There is a bug in conan.cmake that make libraries fail to build if LANGUAGES is specified with only CXX
        LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(dependencies)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(tests)
