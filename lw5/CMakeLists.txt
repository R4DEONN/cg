cmake_minimum_required(VERSION 3.10)
project(Arcanoid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include(FindPkgConfig)
pkg_check_modules(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        App.h
        Model.h
        View.h
        Controller.h
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${GLFW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIRS}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        ${GLFW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        glu32
        gdi32
        opengl32
        user32
        shell32
        dwmapi
)

if(MINGW)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
            "-static-libgcc"
            "-static-libstdc++"
    )
endif()