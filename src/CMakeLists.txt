add_library(fn INTERFACE)
add_library(river::fn ALIAS fn)
target_include_directories(fn INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_features(fn INTERFACE cxx_std_17)
