include(utilities)

if (EXISTS ${CMAKE_SOURCE_DIR}/pyproject.toml)
    include(use_poetry)
    poetry_path(path DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(Conan_DIR ${Conan_DIR} ${path}/Scripts ${path}/bin)
endif ()

find_package(Conan REQUIRED)
download_conan_cmake(conan_cmake DIR ${CMAKE_BINARY_DIR})
include(${conan_cmake})
if (${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/conan.lock)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    conan_cmake_run(
            CONANFILE conanfile.txt
            BUILD missing
    )
endif ()
watch(FILES ${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_BINARY_DIR})
set(CONAN_CMAKE_SILENT_OUTPUT TRUE)
