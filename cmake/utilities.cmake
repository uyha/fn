function(watch)
    set(options ";")
    set(single_values "DIR")
    set(multi_values "FILES")
    cmake_parse_arguments(watch "${options}" "${single_values}" "${multi_values}" ${ARGN})
    if (DEFINED watch_DIR)
        set(dir ${watch_DIR})
    else ()
        set(dir ${CMAKE_CURRENT_SOURCE_DIR})
    endif ()

    set_property(
            DIRECTORY ${dir}
            APPEND
            PROPERTY CMAKE_CONFIGURE_DEPENDS ${watch_FILES}
    )
endfunction()

function(get_home_path out)
    if (DEFINED ENV{HOME})
        set(${out} $ENV{HOME} PARENT_SCOPE)
    else ()
        set(${out} $ENV{HOMEDRIVE}$ENV{HOMEPATH} PARENT_SCOPE)
    endif ()
endfunction()
