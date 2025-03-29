cmake_minimum_required(VERSION 3.10)
project(Maze3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Для поиска GLFW через pkg-config
include(FindPkgConfig)
pkg_check_modules(GLFW REQUIRED glfw3)

# Для поиска OpenGL
find_package(OpenGL REQUIRED)

add_executable(Maze3D main.cpp
        MazeModel.h
        MazeController.h
        MazeView.h
        stb_image.h)

# Добавляем include-директории GLFW и OpenGL
target_include_directories(Maze3D PRIVATE
        ${GLFW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(Maze3D PRIVATE
        ${GLFW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        glu32
        gdi32
        opengl32
        user32
        shell32
        dwmapi
)

if(MINGW)
    target_link_options(Maze3D PRIVATE
            "-static-libgcc"
            "-static-libstdc++"
    )
endif()