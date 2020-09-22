include(${CMAKE_CURRENT_LIST_DIR}/utilities.cmake)

function(conan_version out conan)
    execute_process(
            COMMAND ${conan} --version
            OUTPUT_VARIABLE version
    )
    if (${version} MATCHES ".*Conan version (.*)")
        string(STRIP ${CMAKE_MATCH_1} conan_version)
        set(${out} ${conan_version} PARENT_SCOPE)
    endif ()
endfunction()

function(conan_cache conan)
    conan_version(version ${conan})
    set(CONAN_FOUND TRUE CACHE INTERNAL "")
    set(CONAN_CMD ${conan} CACHE INTERNAL "")
    set(CONAN_VERSION ${version} CACHE INTERNAL "")
endfunction()

function(find_conan_via_pipenv out)
    include(pipenv OPTIONAL RESULT_VARIABLE pipenv)

    if (pipenv STREQUAL pipenv-NOTFOUND)
        message(WARNING "pipenv CMake module is not found, conan will not be searched")
        return()
    endif ()

    found(pipenv_found PIPENV_EXECUTABLE)
    if (NOT pipenv_found)
        message(DEBUG "pipenv is not found, abort searching conan using pipenv")
        return()
    endif ()

    message(STATUS "Finding conan in ${PIPENV_ROOT}")

    find_program(
            CONAN_CMD conan
            HINTS ${PIPENV_ROOT}/Scripts ${PIPENV_ROOT}/bin
            NO_DEFAULT_PATH
            NO_PACKAGE_ROOT_PATH
            NO_CMAKE_PATH
            NO_CMAKE_ENVIRONMENT_PATH
            NO_SYSTEM_ENVIRONMENT_PATH
            NO_CMAKE_SYSTEM_PATH
    )
    found(conan_found CONAN_CMD)
    if (conan_found)
        message(STATUS "conan found at ${CONAN_CMD}")
        set(${out} ${CONAN_CMD} PARENT_SCOPE)
    endif ()
endfunction()

macro(conan_cache_if_found)
    found(conan_found CONAN_CMD)
    if (conan_found)
        conan_cache(${CONAN_CMD})
        return()
    endif ()
endmacro()

function(find_conan)
    message(DEBUG "Checking conan cache")
    conan_cache_if_found()

    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/Pipfile)
        message(DEBUG "No Pipfile in project's root, implicitly opting out of using pipenv to find conan")
    else ()
        message(DEBUG "Finding conan via pipenv")
        find_conan_via_pipenv(CONAN_CMD)
        found(conan_found CONAN_CMD)
        if (conan_found)
            conan_cache(${CONAN_CMD})
            watch(${CMAKE_SOURCE_DIR}/Pipfile)
        endif ()
    endif ()

    message(DEBUG "Finding conan normally")
    find_program(
            CONAN_CMD conan
            HINTS ${Python_ROOT_DIR}/Scripts ${Python_ROOT_DIR}/bin
    )
    conan_cache_if_found()
endfunction()

if (NOT EXISTS ${CMAKE_BINARY_DIR}/conan.cmake)
    message(STATUS "Downloading conan.cmake")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()
include(${CMAKE_BINARY_DIR}/conan.cmake)

if (${CMAKE_SOURCE_DIR}/conanfile.txt IS_NEWER_THAN ${CMAKE_BINARY_DIR}/conan.lock)
    find_conan()
    found(conan_found CONAN_CMD)
    if (NOT conan_found)
        message(WARNING "Aborting conan configuration, conan is not found, please make sure it is installed")
        return()
    endif ()

    if (NOT CMAKE_BUILD_TYPE)
        message(STATUS "CMAKE_BUILD_TYPE is not specified, defaulting to Debug")
        set(CMAKE_BUILD_TYPE Debug)
    endif ()

    conan_cmake_run(
            CONANFILE conanfile.txt
            BUILD missing
    )
    watch(${CMAKE_SOURCE_DIR}/conanfile.txt)
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
set(CONAN_CMAKE_SILENT_OUTPUT TRUE)

