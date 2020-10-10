find_program(Poetry_EXECUTABLE poetry HINTS ${Poetry_DIR})

if (Poetry_EXECUTABLE)
    add_executable(Poetry::Poetry IMPORTED)
    set_target_properties(Poetry::Poetry PROPERTIES IMPORTED_LOCATION "${Poetry_EXECUTABLE}")
    execute_process(
            COMMAND ${Poetry_EXECUTABLE} --version
            RESULT_VARIABLE result
            OUTPUT_VARIABLE version
    )
    if (result EQUAL 0)
        if (${version} MATCHES ".*version(.*)")
            string(STRIP ${CMAKE_MATCH_1} Poetry_VERSION)
        endif ()
    endif ()

    function(poetry_install)
        set(options ";")
        set(single_values DIR)
        set(multi_values OPTIONS)
        cmake_parse_arguments(arg "${options}" "${single_values}" "${multi_values}" ${ARGN})
        if (NOT DEFINED arg_DIR)
            set(arg_DIR ${CMAKE_CURRENT_BINARY_DIR})
            message(NOTICE "DIR is not set, defaulting ${arg_DIR}")
        endif ()
        if (WIN32)
            execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${arg_DIR} cmd /C ${Poetry_EXECUTABLE} install ${arg_OPTIONS})
        else ()
            execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${arg_DIR} ${Poetry_EXECUTABLE} install ${arg_OPTIONS})
        endif ()
    endfunction()

    function(poetry_update)
        set(options ";")
        set(single_values DIR)
        set(multi_values OPTIONS)
        cmake_parse_arguments(arg "${options}" "${single_values}" "${multi_values}" ${ARGN})
        if (NOT DEFINED arg_DIR)
            set(arg_DIR ${CMAKE_CURRENT_BINARY_DIR})
            message(NOTICE "DIR is not set, defaulting ${arg_DIR}")
        endif ()
        if (WIN32)
            execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${arg_DIR} cmd /C ${Poetry_EXECUTABLE} update ${arg_OPTIONS})
        else ()
            execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${arg_DIR} ${Poetry_EXECUTABLE} update ${arg_OPTIONS})
        endif ()
    endfunction()

    function(poetry_path out)
        set(options ";")
        set(single_values DIR)
        set(multi_values ";")
        cmake_parse_arguments(arg "${options}" "${single_values}" "${multi_values}" ${ARGN})
        if (NOT DEFINED arg_DIR)
            set(arg_DIR ${CMAKE_CURRENT_BINARY_DIR})
            message(NOTICE "DIR is not set, defaulting to ${arg_DIR}")
        endif ()
        if (WIN32)
            set(shell_command cmd /C)
        endif ()
        execute_process(COMMAND ${CMAKE_COMMAND} -E chdir ${arg_DIR} ${shell_command} ${Poetry_EXECUTABLE} env info --path
                RESULT_VARIABLE result
                OUTPUT_VARIABLE output)
        string(STRIP ${output} output)
        set(${out} ${output} PARENT_SCOPE)
    endfunction()
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Poetry DEFAULT_MSG Poetry_EXECUTABLE)
