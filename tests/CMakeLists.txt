include(use_conan)
include(CTest)
find_package(Catch2)

macro(construct_test name)
    add_executable(${name} main.cpp ${ARGN})
    target_link_libraries(${name} PRIVATE Catch2::Catch2 river::fn)
    add_test(
            NAME ${name}
            COMMAND ${name})
endmacro()

construct_test(traits traits.test.cpp)
construct_test(free_functions free_functions.test.cpp)
construct_test(member_functions member_functions.test.cpp)
if (NOT MSVC)
    construct_test(sml_integration sml_integration.test.cpp)
    target_link_libraries(sml_integration PRIVATE headers-only)
endif ()
