include(${CMAKE_CURRENT_LIST_DIR}/utilities.cmake)

function(find_poetry)
    find_package(Python REQUIRED)
    if (Poetry_FOUND)
        return()
    endif ()
    if (NOT Poetry_FOUND)
        find_program(Poetry poetry
                HINTS
                "${Poetry_DIR}"
                "${Poetry_DIR}/bin"
                "${Poetry_DIR}/Scripts")
    endif ()
    found(Poetry_FOUND Poetry)
    set(Poetry_FOUND ${Poetry_FOUND} CACHE BOOL "")
    if (Poetry_FOUND)
        message(STATUS "Found poetry: ${Poetry}")
        set(Poetry_SCRIPT ${Poetry} CACHE FILEPATH "")
    else ()
        message(STATUS "poetry could not be found, please specify poetry's location by setting -DPoetry_DIR=/path/to/poetry")
    endif ()
endfunction()

function(poetry_install)
    find_package(Python REQUIRED)
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} ${Python_EXECUTABLE} ${Poetry_SCRIPT} install --no-dev --no-root
    )
endfunction()

function(poetry_update)
    find_package(Python REQUIRED)
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} ${Python_EXECUTABLE} ${Poetry_SCRIPT} update --no-dev
    )
endfunction()

function(poetry_path out)
    find_package(Python REQUIRED)
    execute_process(
            COMMAND ${Python_EXECUTABLE} ${Poetry_SCRIPT} env info --path
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            OUTPUT_VARIABLE result
    )
    string(STRIP ${result} result)
    set(${out} ${result} PARENT_SCOPE)
endfunction()

