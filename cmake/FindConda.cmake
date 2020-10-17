find_program(Conda_EXECUTABLE conda HINTS ${Conda_DIR})

if (Conda_EXECUTABLE AND NOT Conda_FOUND)
    if (NOT TARGET Conda::Conda)
        add_executable(Conda::Conda IMPORTED)
        set_target_properties(Conda::Conda PROPERTIES IMPORTED_LOCATION "${Conda_EXECUTABLE}")
    endif ()
    if (WIN32)
        execute_process(
                COMMAND cmd /C ${Conda_EXECUTABLE} --version
                RESULT_VARIABLE result
                OUTPUT_VARIABLE version
        )
    else ()
        execute_process(
                COMMAND ${Conda_EXECUTABLE} --version
                RESULT_VARIABLE result
                OUTPUT_VARIABLE version
        )
    endif ()
    if (result EQUAL 0)
        if (${version} MATCHES ".*conda(.*)")
            string(STRIP ${CMAKE_MATCH_1} Conda_VERSION)
        endif ()
    endif ()
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Conda
        REQUIRED_VARS Conda_EXECUTABLE
        VERSION_VAR Conda_VERSION)
