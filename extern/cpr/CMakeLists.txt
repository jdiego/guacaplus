message(STATUS "Downloading CPR .")
    if (APPLE)
        set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
        set(OPENSSL_LIBRARIES /usr/local/opt/openssl/lib)
        message(STATUS "OpenSSL Version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
    #
        message(STATUS "Using PKG_Config to search for libcurl.")
        pkg_search_module(PKG_CURL REQUIRED IMPORTED_TARGET libcurl)
    endif()
    find_package(openssl REQUIRED)

    # CURL
    find_package(CURL)
    if (CURL_FOUND)
        set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
    endif() 

    set(USE_SYSTEM_GTEST OFF)
    set(BUILD_CPR_TESTS OFF)

    FetchContent_Declare(
        cpr 
        GIT_REPOSITORY https://github.com/whoshuu/cpr.git
    )
    FetchContent_MakeAvailable(cpr)
    # Adds cpr::cpr
    message(STATUS "Exporting cpr::cpr target.")
