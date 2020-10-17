include(use_conan)

find_package(benchmark REQUIRED)
find_package(Git REQUIRED)
find_package(Conda REQUIRED)

add_custom_command(
        OUTPUT benchmark/tools/compare.py
        COMMAND ${CMAKE_COMMAND} -E make_directory benchmark
        COMMAND Git::Git -C benchmark init
        COMMAND Git::Git -C benchmark config core.sparseCheckout true
        COMMAND ${CMAKE_COMMAND} -E echo tools >> benchmark/.git/info/sparse-checkout
        COMMAND Git::Git -C benchmark pull https://github.com/google/benchmark.git master
)

function(bootstrap_bm name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE benchmark::benchmark)
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/benchmarks/helpers)
    target_compile_features(${name} PUBLIC cxx_std_20)
    add_dependencies(bm ${name})
endfunction()

function(boostrap_bm_compare name baseline contender)
    add_custom_target(
            ${name}
            COMMAND Conda::Conda run benchmark/tools/compare.py benchmarks $<TARGET_FILE:${baseline}> $<TARGET_FILE:${contender}>
            DEPENDS benchmark/tools/compare.py
    )
endfunction()

add_custom_target(bm ALL)

add_subdirectory(free_functions)

boostrap_bm_compare(bm_compare_free_functions bm_free_functions_direct bm_free_functions_fn)
