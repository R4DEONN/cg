cmake_minimum_required(VERSION 3.10)
project(asteroids)

set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(OpenGL REQUIRED)

add_executable(asteroids
        main.cpp
        framework.h
        libgl/framework.h
        libgl/libgl.h
        libgl/libgl.cpp
        libgl/pch.h
        libgl/pch.cpp
)

target_link_libraries(asteroids PRIVATE
        OpenGL::GL
)

target_include_directories(asteroids PRIVATE
        ${OPENGL_INCLUDE_DIR}
)