# - C++ Requests, Curl for People
# This module is a libcurl wrapper written in modern C++.
# It provides an easy, intuitive, and efficient interface to
# a host of networking methods.
#
# Finding this module will define the following variables:
#  CPR_FOUND - True if the core library has been found
#  CPR_LIBRARIES - Path to the core library archive
#  CPR_INCLUDE_DIRS - Path to the include directories. Gives access
#                     to cpr.h, which must be included in every
#                     file that uses this interface

find_path(CPR_INCLUDE_DIR NAMES cpr/cpr.h)

find_library(CPR_LIBRARY NAMES cpr HINTS ${CPR_LIBRARY_ROOT})

mark_as_advanced(CPR_FOUND CPR_INCLUDE_DIR CPR_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(cpr 
    REQUIRED_VARS CPR_LIBRARY CPR_INCLUDE_DIR
    VERSION_VAR CPR_VERSION
)

if (CPR_FOUND)
    #Set include dirs to parent, to enable includes like #include <cpr/cpr.h>
    get_filename_component(CPR_INCLUDE_DIRS ${CPR_INCLUDE_DIR} DIRECTORY)
endif()

if(CPR_FOUND AND NOT TARGET cpr::cpr)
    set(CPR_LIBRARIES ${CPR_LIBRARY})
    set(CPR_INCLUDE_DIRS ${CPR_INCLUDE_DIR})
    add_library(cpr::cpr SHARED IMPORTED GLOBAL)
    set_target_properties(cpr::cpr PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CPR_INCLUDE_DIR}"
        IMPORTED_LOCATION "${CPR_LIBRARY}"
    )
endif()
