bootstrap_bm(bm_free_functions_direct functions.cpp benchmark.cpp)
target_compile_definitions(bm_free_functions_direct PRIVATE MODE=DIRECT)

bootstrap_bm(bm_free_functions_fn functions.cpp benchmark.cpp)
target_link_libraries(bm_free_functions_fn PRIVATE river::fn)
target_compile_definitions(bm_free_functions_fn PRIVATE MODE=WRAP)
