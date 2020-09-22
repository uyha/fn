function(pipenv_install)
    if (NOT PIPENV_FOUND)
        message(WARNING "pipenv is not found, aborting pipenv install")
        return()
    endif ()
    # Compare to see if the content of Pipfile in the build directory is different
    # than the one in the source directory. If they are different, then copy the
    # Pipfile in the source directory to the build directory.
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_SOURCE_DIR}/Pipfile ${CMAKE_BINARY_DIR}/Pipfile
            RESULT_VARIABLE different_pipfile
            OUTPUT_QUIET
            ERROR_QUIET
    )
    if (different_pipfile)
        message(DEBUG "Copying Pipfile to ${CMAKE_BINARY_DIR}")
        file(COPY ${CMAKE_SOURCE_DIR}/Pipfile DESTINATION ${CMAKE_BINARY_DIR})
    endif ()

    # If the build directory Pipfile gets changed after Pipfile.lock is generated,
    # rerun pipenv install to make sure they are in sync
    if (${CMAKE_BINARY_DIR}/Pipfile IS_NEWER_THAN ${CMAKE_BINARY_DIR}/Pipfile.lock)
        message(STATUS "Installing python requirements from Pipfile")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} ${PIPENV_EXECUTABLE} install
                RESULT_VARIABLE error
                ERROR_VARIABLE error_message
                OUTPUT_QUIET
                ERROR_QUIET
        )
        if (error)
            if (error_message)
                message(FATAL_ERROR "${error_message}")
            else ()
                message(FATAL_ERROR "${error}")
            endif ()
        endif ()
    endif ()
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} ${PIPENV_EXECUTABLE} --venv
            OUTPUT_VARIABLE pipenv_root
    )
    string(STRIP ${pipenv_root} pipenv_root)
    set(PIPENV_ROOT ${pipenv_root} CACHE INTERNAL "")
endfunction()

if (NOT PIPENV_FOUND)
    include(${CMAKE_CURRENT_LIST_DIR}/utilities.cmake)
    get_home_path(home)
    find_package(Python REQUIRED)
    execute_process(
            COMMAND ${Python_EXECUTABLE} -c "import sys; print(sys.prefix)"
            OUTPUT_VARIABLE python_root
    )
    string(STRIP ${python_root} python_root)
    set(pipenv_search_path
            ${python_root}/Scripts
            ${python_root}/bin
            ${home}/.local/bin
            ${PIPENV_LOCATION} $ENV{PATH})
    message(DEBUG "Finding pipenv in ${pipenv_search_path}")
    find_program(
            PIPENV_EXECUTABLE
            pipenv
            HINTS ${pipenv_search_path}
            NO_DEFAULT_PATH
            NO_PACKAGE_ROOT_PATH
            NO_CMAKE_PATH
            NO_CMAKE_ENVIRONMENT_PATH
            NO_SYSTEM_ENVIRONMENT_PATH
            NO_CMAKE_SYSTEM_PATH
    )
    if (PIPENV_EXECUTABLE STREQUAL PIPENV_EXECUTABLE-NOTFOUND)
        message(WARNING "pipenv could not be found at ${python_root}, please make sure it is installed")
        return()
    endif ()

    message(STATUS "Found pipenv: ${PIPENV_EXECUTABLE}")
    set(PIPENV_EXECUTABLE "${PIPENV_EXECUTABLE}" CACHE INTERNAL "")
    set(PIPENV_FOUND TRUE CACHE INTERNAL "")

    if (EXISTS ${CMAKE_SOURCE_DIR}/Pipfile)
        pipenv_install()
    endif ()
endif ()
