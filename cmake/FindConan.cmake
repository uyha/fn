find_program(Conan_EXECUTABLE conan HINTS ${Conan_DIR})

if (Conan_EXECUTABLE)
    set(CONAN_CMD ${Conan_EXECUTABLE})
    if (NOT TARGET Conan::Conan)
        add_executable(Conan::Conan IMPORTED)
        set_target_properties(Conan::Conan PROPERTIES IMPORTED_LOCATION "${Conan_EXECUTABLE}")
    endif ()
    if (WIN32)
        execute_process(
                COMMAND cmd /C ${Conan_EXECUTABLE} --version
                RESULT_VARIABLE result
                OUTPUT_VARIABLE version
        )
    else ()
        execute_process(
                COMMAND ${Conan_EXECUTABLE} --version
                RESULT_VARIABLE result
                OUTPUT_VARIABLE version
        )
    endif ()
    if (result EQUAL 0)
        if (${version} MATCHES ".*version(.*)")
            string(STRIP ${CMAKE_MATCH_1} Conan_VERSION)
        endif ()
    endif ()

    function(download_conan_cmake out)
        set(options ";")
        set(single_values DIR)
        set(multi_values ";")
        cmake_parse_arguments(arg "${options}" "${single_values}" "${multi_values}" ${ARGN})
        if (NOT DEFINED arg_DIR)
            set(arg_DIR "${CMAKE_CURRENT_BINARY_DIR}")
            message(NOTICE "DIR is not set, defaulting to ${arg_DIR}")
        endif ()

        if (NOT EXISTS ${arg_DIR}/conan.cmake)
            file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                    "${arg_DIR}/conan.cmake"
                    STATUS download_status)
            list(POP_FRONT download_status download_error)
            if (NOT download_error EQUAL 0)
                file(REMOVE ${arg_DIR}/conan.cmake)
                message(FATAL_ERROR "Failed to download conan.cmake")
            endif ()
        endif ()
        set(${out} ${arg_DIR}/conan.cmake PARENT_SCOPE)
    endfunction()
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Conan
        REQUIRED_VARS Conan_EXECUTABLE
        VERSION_VAR Conan_VERSION)
