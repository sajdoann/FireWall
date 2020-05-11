cmake_minimum_required(VERSION 3.10)
project(FireWall)

set(CMAKE_CXX_STANDARD 14)

add_executable(FireWall sajdoann/src/main.cpp sajdoann/src/App.cpp sajdoann/src/App.h sajdoann/src/Game/Game.h sajdoann/src/Game/ResultEnum.h sajdoann/src/Game/State.enum sajdoann/src/IOLoaders/Reader.h sajdoann/src/Objects/Object.h sajdoann/src/Objects/MovingObject.h sajdoann/src/Objects/Patch.h
        sajdoann/src/Objects/Coords.h sajdoann/src/Board/Board.h sajdoann/src/Objects/Empty.h sajdoann/src/Interface.cpp sajdoann/src/Interface.h sajdoann/src/Command.h sajdoann/src/CommandEndType.h sajdoann/src/Objects/Virus.h sajdoann/src/Commands.h sajdoann/src/Messages.h sajdoann/src/Objects/Hotfix.h sajdoann/src/IOLoaders/Writer.h sajdoann/src/Game/ScoreCounter.h sajdoann/src/Movement/MovementFunction.h sajdoann/src/Movement/Movement.h sajdoann/src/Movement/MovementType.h sajdoann/src/Movement/MovementDirection.h sajdoann/src/Board/Board.cpp sajdoann/src/Game/VirusWave.h sajdoann/src/Color.h sajdoann/src/Objects/MovingInterface.h sajdoann/src/Objects/ObjectWithMoveAttributes.h)