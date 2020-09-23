include(CTest)
find_package(Catch2)
find_package(fmt)

macro(construct_test name)
    add_executable(${name} main.cpp ${ARGN})
    target_link_libraries(${name} PRIVATE Catch2::Catch2 fmt::fmt fn::fn)
    target_compile_features(${name} PRIVATE cxx_std_17)
    add_test(
            NAME ${name}
            COMMAND ${name})
endmacro()

construct_test(free_functions free_functions.cpp)
construct_test(member_functions member_functions.cpp)
construct_test(sml_integration sml_integration.cpp)
target_link_libraries(sml_integration PRIVATE headers-only)
