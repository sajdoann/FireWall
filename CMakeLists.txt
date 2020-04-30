cmake_minimum_required(VERSION 3.10)
project(FireWall)

set(CMAKE_CXX_STANDARD 14)

add_executable(FireWall src/main.cpp src/App.cpp src/App.h src/Game/Game.cpp src/Game/Game.h src/Game/GameResult.enum src/Game/GameState.enum src/Readers/AbstractReader.h src/Objects/AbstractObject.h src/Objects/MovingObject.h src/Objects/Patch.h src/Objects/MovementType.enum)