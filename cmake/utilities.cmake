function(found out in)
    if (DEFINED ${in} AND NOT ${${in}} STREQUAL ${in}-NOTFOUND)
        set(${out} TRUE PARENT_SCOPE)
    else ()
        set(${out} FALSE PARENT_SCOPE)
    endif ()
endfunction()

function(watch)
    set_property(
            DIRECTORY
            APPEND
            PROPERTY CMAKE_CONFIGURE_DEPENDS ${ARGV}
    )
endfunction()

function(get_home_path out)
    if (DEFINED ENV{HOME})
        set(${out} $ENV{HOME} PARENT_SCOPE)
    else ()
        set(${out} $ENV{HOMEDRIVE}$ENV{HOMEPATH} PARENT_SCOPE)
    endif ()
endfunction()

function(set_if_not var)
    if (NOT ${var})
        set(${var} ${ARGN} PARENT_SCOPE)
    endif ()
endfunction()