file(GLOB SRC "library/*.cpp")
message("source_code=${SRC}")
file(GLOB GLTOOLS "gltools/*.cpp")
message("source_code=${GLTOOLS}")
add_library(minor_computer_vision SHARED ${SRC})
add_library(gltools SHARED ${GLTOOLS})

add_executable(vind_rechthoek rechthoek.cpp)
add_executable(vind_patroon_schaakbord vind_patroon_schaakbord.cpp)
add_executable(calibratie_schaakbord calibratie_schaakbord.cpp)
    
#libraries check, en instellingen
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
find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
  message("===== Found OpenGL =====")
  include_directories(${OPENGL_INCLUDE_DIRS})
  target_link_libraries(minor_computer_vision ${OpenGL_LIBRARIES})
  target_link_libraries(gltools ${OpenGL_LIBRARIES})
endif(OpenGL_FOUND)

target_link_libraries(vind_rechthoek ${OpenCV_LIBS} ${SFML_LIBRARIES} minor_computer_vision gltools)
target_link_libraries(vind_patroon_schaakbord ${OpenCV_LIBS} ${SFML_LIBRARIES}   minor_computer_vision gltools)
target_link_libraries(calibratie_schaakbord ${OpenCV_LIBS} ${SFML_LIBRARIES} minor_computer_vision gltools)
