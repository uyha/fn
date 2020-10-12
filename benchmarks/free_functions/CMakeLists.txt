bootstrap_bm(bm_free_functions_direct functions.cpp direct.benchmark.cpp)
bootstrap_bm(bm_free_functions_fn functions.cpp fn.benchmark.cpp)
target_link_libraries(bm_free_functions_fn PRIVATE river::fn)
