cmake_minimum_required(VERSION 3.10)
project(asteroids)

set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(asteroids
        View/GLApplication.cpp
        View/GLApplication.h
        View/AsteroidsView.cpp
        View/AsteroidsView.h
        Disposable.h
        app.cpp
        controller/AsteroidsController.h
        model/AsteroidsModel.h
        model/PlayerModel.h
        model/AsteroidManager.h
        model/Asteroid.h
        model/Moveable.cpp
        model/Movable.h
        view/PlayerView.h
        view/AsteroidView.h
        model/Bullet.h
        view/BulletView.h
        model/Constants.h
        view/Renderer.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
