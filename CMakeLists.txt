cmake_minimum_required(VERSION 3.10)
project(FireWall)

set(CMAKE_CXX_STANDARD 14)

add_executable(FireWall sajdoann/src/main.cpp sajdoann/src/App.cpp sajdoann/src/App.h sajdoann/src/Game/Game.h sajdoann/src/Game/ResultEnum.h sajdoann/src/Game/State.enum sajdoann/src/Game/IOLoaders/Reader.h sajdoann/src/Game/Objects/Object.h sajdoann/src/Game/Objects/MovingObject.h sajdoann/src/Game/Objects/Patch.h
        sajdoann/src/Game/Objects/Coords.h
        sajdoann/src/Game/Board/Board.h
        sajdoann/src/Game/Objects/Empty.h sajdoann/src/Interface.cpp sajdoann/src/Interface.h sajdoann/src/Command.h sajdoann/src/CommandEndType.h sajdoann/src/Game/Objects/Virus.h sajdoann/src/Commands.h sajdoann/src/Messages.h sajdoann/src/Game/Objects/Hotfix.h sajdoann/src/Game/IOLoaders/Writer.h sajdoann/src/Game/ScoreCounter.h sajdoann/src/Game/Movement/MovementFunction.h
        sajdoann/src/Game/Movement/Movement.h sajdoann/src/Game/Movement/MovementType.h sajdoann/src/Game/Movement/MovementDirection.h sajdoann/src/Game/Board/Board.cpp sajdoann/src/Game/VirusWave.h sajdoann/src/Color.h sajdoann/src/Game/Objects/ObjectWithMoveAttributes.h sajdoann/src/constants.h sajdoann/src/Game/Objects/Patch.cpp sajdoann/src/Game/Objects/Virus.cpp sajdoann/src/Game/Objects/Hotfix.cpp sajdoann/src/Game/Objects/Empty.cpp sajdoann/src/Game/Strategics/Strategy.h sajdoann/src/Game/Strategics/StraightStrategy.h sajdoann/src/Game/Strategics/StraightStrategy.cpp sajdoann/src/Game/Strategics/Strategy.cpp sajdoann/src/Game/Objects/Coords.cpp)