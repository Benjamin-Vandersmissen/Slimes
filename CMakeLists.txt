cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME Slimes)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Slime.cpp Slime.h Object.cpp Object.h Window.cpp Window.h Wall.cpp Wall.h Room.cpp Room.h Projectile.cpp Projectile.h ControllableObject.cpp ControllableObject.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)