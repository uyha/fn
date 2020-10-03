include(${CMAKE_CURRENT_LIST_DIR}/utilities.cmake)

function(conan_version Conan_EXECTUABLE out)
    execute_process(
            COMMAND ${CONAN_CMD} --version
            OUTPUT_VARIABLE version
    )
    if (${version} MATCHES ".*Conan version (.*)")
        string(STRIP ${CMAKE_MATCH_1} conan_version)
        set(${out} ${conan_version} PARENT_SCOPE)
    endif ()
endfunction()

function(find_conan_via_pipenv)
    include(${CMAKE_CURRENT_LIST_DIR}/pipenv)
    found(pipenv_found PIPENV_EXECUTABLE)
    if (NOT pipenv_found)
        message(DEBUG "pipenv is not found, abort searching conan using pipenv")
        return()
    endif ()

    message(STATUS "Finding conan in ${PIPENV_ROOT}")

    find_program(CONAN_CMD conan HINTS ${PIPENV_ROOT}/Scripts ${PIPENV_ROOT}/bin)
    found(CONAN_FOUND CONAN_CMD)
    if (NOT CONAN_FOUND)
        message(DEBUG "conan could not be found via pipenv")
        return()
    endif ()

    message(STATUS "conan found at ${CONAN_CMD}")

    conan_version(${CONAN_CMD} CONAN_VERSION)
    set(CONAN_FOUND ${CONAN_FOUND} CACHE BOOL "")
    set(CONAN_CMD ${CONAN_CMD} CACHE FILEPATH "")
    set(CONAN_VERSION ${CONAN_VERSION} CACHE STRING "")
endfunction()

function(find_conan_via_poetry)
    include(${CMAKE_CURRENT_LIST_DIR}/poetry.cmake)
    message(DEBUG "Finding poetry")
    find_poetry()
    if (NOT Poetry_FOUND)
        return()
    endif ()

    message(DEBUG "Generating poetry environment")
    if (${CMAKE_SOURCE_DIR}/pyproject.toml IS_NEWER_THAN ${CMAKE_BINARY_DIR}/poetry.lock)
        file(COPY ${CMAKE_SOURCE_DIR}/pyproject.toml DESTINATION ${CMAKE_BINARY_DIR})
        if (EXISTS ${CMAKE_BINARY_DIR}/poetry.lock)
            poetry_update()
        else ()
            poetry_install()
        endif ()
    endif ()

    poetry_path(root_path)
    find_program(CONAN_CMD NAMES conan HINTS ${root_path}/bin ${root_path}/Scripts)
    found(CONAN_FOUND CONAN_CMD)

    if (NOT CONAN_FOUND)
        message(DEBUG "conan could not be found via poetry")
        return()
    endif ()

    message(STATUS "Found conan: ${CONAN_CMD}")

    conan_version(${CONAN_CMD} CONAN_VERSION)
    set(CONAN_FOUND ${CONAN_FOUND} CACHE BOOL "")
    set(CONAN_CMD ${CONAN_CMD} CACHE FILEPATH "")
    set(CONAN_VERSION ${CONAN_VERSION} CACHE STRING "")
endfunction()

function(find_conan)
    message(DEBUG "Checking conan cache")
    if (CONAN_FOUND)
        return()
    endif ()

    # Finding conan by creating the pipenv environment specified in the project's root
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/Pipfile)
        message(DEBUG "No pipfile in the project's root, skipping pipenv")
    else ()
        find_conan_via_pipenv()
        if (CONAN_FOUND)
            watch(${CMAKE_SOURCE_DIR}/Pipfile)
            return()
        endif ()
    endif ()

    # Finding conan by creating the poetry environment specified in the project's root
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/pyproject.toml)
        message(DEBUG "No pyproject.toml in the project's root, skipping poetry")
    else ()
        find_conan_via_poetry()

        if (CONAN_FOUND)
            watch(${CMAKE_SOURCE_DIR}/pyproject.toml)
            return()
        endif ()
    endif ()

    message(DEBUG "Finding conan normally")
    find_program(
            CONAN_CMD conan
            HINTS ${CONAN_DIR}
    )
endfunction()

if (${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/conan.lock)
    find_conan()
    if (NOT CONAN_FOUND)
        message(WARNING "Aborting conan configuration, conan is not found, please make sure it is installed")
        return()
    endif ()

    if (NOT CMAKE_BUILD_TYPE)
        message(STATUS "CMAKE_BUILD_TYPE is not specified, defaulting to Debug")
        set(CMAKE_BUILD_TYPE Debug)
    endif ()

    if (NOT EXISTS ${CMAKE_BINARY_DIR}/conan.cmake)
        message(STATUS "Downloading conan.cmake")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
    endif ()
    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_run(
            CONANFILE conanfile.txt
            BUILD missing
    )
endif ()
watch(${CMAKE_CURRENT_SOURCE_DIR}/conanfile.txt)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_BINARY_DIR})
set(CONAN_CMAKE_SILENT_OUTPUT TRUE)

