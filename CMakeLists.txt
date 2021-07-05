cmake_minimum_required(VERSION 3.10)

project(lucidity)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lucidity 
			   src/lucidity.cpp 
			   src/shader.cpp 
			   src/game.cpp 
			   src/globals.cpp
			   src/stb_image.cpp
			   src/camera.cpp
			   src/sprite.cpp
			   src/map.cpp
			   src/collisionmap.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glfw" "${PROJECT_SOURCE_DIR}/lib/glfw/build")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glm" "${PROJECT_SOURCE_DIR}/lib/glm/build")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glad" "${PROJECT_SOURCE_DIR}/lib/glad/build")

include_directories("${PROJECT_SOURCE_DIR}/lib/glfw/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/glm")
include_directories("${PROJECT_SOURCE_DIR}/lib/glad")

target_link_libraries(lucidity glfw ${GLFW_LIBRARIES})
target_link_libraries(lucidity glad)
target_link_libraries(lucidity glm)