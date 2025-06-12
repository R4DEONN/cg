cmake_minimum_required(VERSION 3.10)
project(Morphing)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Поиск зависимостей
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(GLUT REQUIRED)

add_executable(Morphing main.cpp
        Camera.cpp
        Camera.h
        Application.cpp
        Application.h)

# Подключение заголовочных путей
target_include_directories(Morphing PRIVATE
        ${GLUT_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS})

# Подключение библиотек
target_link_libraries(Morphing PRIVATE
        glfw
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${GLUT_LIBRARIES}
        opengl32
        glu32
)