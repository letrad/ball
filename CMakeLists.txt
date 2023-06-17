cmake_minimum_required(VERSION 3.12)
project(ball)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(ball ball.cpp)

target_link_libraries(small3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# Additional linking flags
set_target_properties(ball PROPERTIES LINK_FLAGS "-lGL -lGLU -lglut")
