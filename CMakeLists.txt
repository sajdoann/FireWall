cmake_minimum_required(VERSION 3.10)
project(FireWall)

set(CMAKE_CXX_STANDARD 14)

add_executable(FireWall sajdoann/src/main.cpp sajdoann/src/App.cpp sajdoann/src/App.h sajdoann/src/Game/Game.h sajdoann/src/Game/Result.enum sajdoann/src/Game/State.enum sajdoann/src/Readers/Reader.h sajdoann/src/Objects/Object.h sajdoann/src/Objects/MovingObject.h sajdoann/src/Objects/Patch.h sajdoann/src/Objects/MovementType.enum
        sajdoann/src/Objects/Coords.h sajdoann/src/Board/Board.h sajdoann/src/Objects/Empty.h sajdoann/src/Interface.cpp sajdoann/src/Interface.h sajdoann/src/Command.h sajdoann/src/CommandEndType.h sajdoann/src/Objects/Virus.h sajdoann/src/Commands.h sajdoann/src/Messages.h sajdoann/src/Objects/Hotfix.h)