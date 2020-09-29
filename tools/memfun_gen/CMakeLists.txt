find_package(range-v3 REQUIRED)
find_package(cxxopts REQUIRED)
find_package(fmt REQUIRED)

add_executable(memfn_gen memfn_gen.cpp)
target_link_libraries(memfn_gen PRIVATE range-v3::range-v3 cxxopts::cxxopts fmt::fmt)
target_compile_features(memfn_gen PRIVATE cxx_std_20)
