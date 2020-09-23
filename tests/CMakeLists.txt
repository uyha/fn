include(CTest)
find_package(Catch2)
find_package(fmt)

macro(construct_test name)
    add_executable(${name} main.cpp ${ARGN})
    target_link_libraries(${name} PRIVATE Catch2::Catch2 fmt::fmt fn::fn)
    add_test(
            NAME ${name}
            COMMAND ${name})
endmacro()

construct_test(free_functions free_functions.cpp)
construct_test(member_functions member_functions.cpp)
