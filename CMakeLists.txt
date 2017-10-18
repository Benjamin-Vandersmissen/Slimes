cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME Slimes)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Slime.cpp Slime.h Object.cpp Object.h Game.cpp Game.h Wall.cpp Wall.h Room.cpp Room.h Projectile.cpp Projectile.h ControllableObject.cpp ControllableObject.h Person.cpp Person.h ClimbSlime.cpp ClimbSlime.h WallSlime.cpp WallSlime.h Tileset.cpp Tileset.h AnimatedSprite.cpp AnimatedSprite.h View.cpp View.h Key.cpp Key.h Door.cpp Door.h SlimesGame.cpp SlimesGame.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system pthread)