set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

# Following block can broke build in case of cross-compilng
# but CMAKE_CROSSCOMPILING variable will be set only on project(OpenCV) command
# so we will try to detect crosscompiling by presense of CMAKE_TOOLCHAIN_FILE
if(NOT CMAKE_TOOLCHAIN_FILE)
    # Add these standard paths to the search paths for FIND_LIBRARY
    # to find libraries from these locations first
    if(UNIX)
        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib)
    endif()

    # it _must_ go before PROJECT(OpenCV) in order to work
    if(WIN32)
        set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory")
    else()
        set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Installation Directory")
    endif()

    if(MSVC)
        set(CMAKE_USE_RELATIVE_PATHS ON CACHE INTERNAL "" FORCE)
    endif()
endif(NOT CMAKE_TOOLCHAIN_FILE)

project(minor_computer_vision)
add_subdirectory(src)
