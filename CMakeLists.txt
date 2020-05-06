cmake_minimum_required(VERSION 3.10)
project(FireWall)

set(CMAKE_CXX_STANDARD 14)

add_executable(FireWall src/main.cpp src/App.cpp src/App.h src/Game/Game.h src/Game/Result.enum src/Game/State.enum src/Readers/Reader.h src/Objects/Object.h src/Objects/MovingObject.h src/Objects/Patch.h src/Objects/MovementType.enum
        src/Objects/Coords.h src/Board/Board.h src/Objects/Empty.h src/Interface.cpp src/Interface.h src/Command.h src/CommandEndType.h src/Objects/Virus.h src/Commands.h src/Messages.h)