add_executable(bm_free_functions_direct functions.cpp direct.benchmark.cpp)
target_link_libraries(bm_free_functions_direct PRIVATE benchmark::benchmark river::fn)
