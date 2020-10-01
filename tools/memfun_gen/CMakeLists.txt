include(dependencies)
include(build_options)

find_package(range-v3 REQUIRED)
find_package(cxxopts REQUIRED)
find_package(fmt REQUIRED)
find_package(ctre REQUIRED)

add_executable(memfn_gen memfn_gen.cpp)
target_link_libraries(memfn_gen PRIVATE range-v3::range-v3 cxxopts::cxxopts fmt::fmt ctre::ctre)
set_target_properties(memfn_gen PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_compile_features(memfn_gen PRIVATE cxx_std_20)
target_compile_options(memfn_gen PRIVATE ${warnings} ${wae})
