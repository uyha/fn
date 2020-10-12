include(use_conan)

find_package(benchmark REQUIRED)
find_package(Git REQUIRED)
add_custom_command(
        OUTPUT benchmark/tools/compare.py
        COMMAND ${CMAKE_COMMAND} -E make_directory benchmark
        COMMAND Git::Git -C benchmark init
        COMMAND Git::Git -C benchmark config core.sparseCheckout true
        COMMAND ${CMAKE_COMMAND} -E echo tools >> benchmark/.git/info/sparse-checkout
        COMMAND Git::Git -C benchmark pull https://github.com/google/benchmark.git master
)
add_custom_target(pull_compare DEPENDS benchmark/tools/compare.py)

function(bootstrap_bm name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE benchmark::benchmark)
    target_compile_features(${name} PRIVATE cxx_std_20)
    add_dependencies(bm ${name})
endfunction()

add_custom_target(bm ALL)

add_subdirectory(free_functions)
