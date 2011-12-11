
set (SRC
    gui/gui.cpp
    gui/gui.h
    gui/window_2d.cpp
    gui/window_2d.h
    library/algorithms.cpp
    library/algorithms.h
    library/input.cpp
    library/input.h
    library/library.h
    library/resource.cpp
    library/resource.h
    lua/lua.h
    lua/lua_loader.cpp
    main.cpp
    )
    
add_executable(minor_computer_vision ${SRC})
    
    #libraries check, en instellingen
find_package(Lua51 REQUIRED)
if (LUA51_FOUND)
	message("===== LUA Found =====")
    include_directories(${LUA_INCLUDE_DIRS})
    target_link_libraries(minor_computer_vision ${LUA_LIBRARIES})
endif (LUA51_FOUND)
find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
	message("=====Found OpenCV version ${OpenCV_VERSION} =====")
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(minor_computer_vision ${OpenCV_LIBS})
endif (OpenCV_FOUND)
find_package(SFML COMPONENTS system graphics window REQUIRED)
if (SFML_FOUND)
	message("===== SFML Found =====")
    include_directories(${SFML_INCLUDE_DIRS})
    target_link_libraries(minor_computer_vision ${SFML_LIBRARIES})
endif (SFML_FOUND)
find_package(Luabind REQUIRED)
if (LUABIND_FOUND)
	message("===== LUAbind Found =====")
    include_directories(${LUABIND_INCLUDE_DIR})
    target_link_libraries(minor_computer_vision ${LUABIND_LIBRARY})
endif(LUABIND_FOUND)



                                
