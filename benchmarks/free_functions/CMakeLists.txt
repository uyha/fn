add_executable(bm_free_functions_direct functions.cpp direct.benchmark.cpp)
target_link_libraries(bm_free_functions_direct PRIVATE benchmark::benchmark)

add_executable(bm_free_functions_fn functions.cpp fn.benchmark.cpp)
target_link_libraries(bm_free_functions_fn PRIVATE benchmark::benchmark river::fn)
