CXX=g++
CXXFLAGS = -Wall -pedantic -g -Og -std=c++14
LD=g++
LDFLAGS =-fsanitize=address
${EXECUTABLE}: Interface.o main.o
	${LD} ${LDFLAGS} $^ -o ${EXECUTABLE}


%.o: src/%.cpp

 Game/Board/Board.h Game/Board/../Objects/Object.h \
 Game/Board/../Objects/Empty.h Game/Board/../Objects/Patch.h \
 Game/Board/../Objects/ObjectWithMoveAttributes.h \
 Game/Board/../Objects/../Movement/MovementType.h \
 Game/Board/../Objects/../Movement/MovementDirection.h \
 Game/Board/../Objects/Hotfix.h Game/Board/../Objects/MovingObject.h \
 Game/Board/../Objects/../Strategics/Strategy.h \
 Game/Board/../Objects/../Strategics/FrontStrategy.h \
 Game/Board/../Objects/../Strategics/RandomStrategy.h \
 Game/Board/../Objects/../Strategics/BfsStrategy.h \
 Game/Board/../IOLoaders/Reader.h \
 Game/Board/../IOLoaders/../Objects/Virus.h Game/ResultEnum.h Color.h \
 Interface_Constants.h


Coords.o: Coords.cpp Coords.h ../Board/Board.h \
 ../Board/../Objects/Object.h ../Board/../Objects/Empty.h \
 ../Board/../Objects/Patch.h \
 ../Board/../Objects/ObjectWithMoveAttributes.h \
 ../Board/../Objects/../Movement/MovementType.h \
 ../Board/../Objects/../Movement/MovementDirection.h \
 ../Board/../Objects/Hotfix.h ../Board/../Objects/MovingObject.h \
 ../Board/../Objects/../Strategics/Strategy.h \
 ../Board/../Objects/../Strategics/FrontStrategy.h \
 ../Board/../Objects/../Strategics/RandomStrategy.h \
 ../Board/../Objects/../Strategics/BfsStrategy.h \
 ../Board/../IOLoaders/Reader.h ../Board/../IOLoaders/../Objects/Virus.h
Empty.o: Empty.cpp Empty.h Object.h Coords.h ../Board/Board.h \
 ../Board/../Objects/Patch.h \
 ../Board/../Objects/ObjectWithMoveAttributes.h \
 ../Board/../Objects/../Movement/MovementType.h \
 ../Board/../Objects/../Movement/MovementDirection.h \
 ../Board/../Objects/Hotfix.h ../Board/../Objects/MovingObject.h \
 ../Board/../Objects/../Strategics/Strategy.h \
 ../Board/../Objects/../Strategics/FrontStrategy.h \
 ../Board/../Objects/../Strategics/RandomStrategy.h \
 ../Board/../Objects/../Strategics/BfsStrategy.h \
 ../Board/../IOLoaders/Reader.h ../Board/../IOLoaders/../Objects/Virus.h
Hotfix.o: Hotfix.cpp Hotfix.h Object.h Coords.h MovingObject.h \
 ObjectWithMoveAttributes.h ../Movement/MovementType.h \
 ../Movement/MovementDirection.h ../Strategics/Strategy.h \
 ../Strategics/FrontStrategy.h ../Strategics/RandomStrategy.h \
 ../Strategics/BfsStrategy.h ../Board/Board.h ../Board/../Objects/Empty.h \
 ../Board/../Objects/Patch.h ../Board/../IOLoaders/Reader.h \
 ../Board/../IOLoaders/../Objects/Virus.h
Patch.o: Patch.cpp Patch.h ObjectWithMoveAttributes.h \
 ../Movement/MovementType.h ../Movement/MovementDirection.h Object.h \
 Coords.h Hotfix.h MovingObject.h ../Strategics/Strategy.h \
 ../Strategics/FrontStrategy.h ../Strategics/RandomStrategy.h \
 ../Strategics/BfsStrategy.h ../Board/Board.h ../Board/../Objects/Empty.h \
 ../Board/../IOLoaders/Reader.h ../Board/../IOLoaders/../Objects/Virus.h
Virus.o: Virus.cpp Virus.h MovingObject.h Object.h Coords.h \
 ObjectWithMoveAttributes.h ../Movement/MovementType.h \
 ../Movement/MovementDirection.h ../Strategics/Strategy.h \
 ../Strategics/FrontStrategy.h ../Strategics/RandomStrategy.h \
 ../Strategics/BfsStrategy.h ../Board/Board.h ../Board/../Objects/Empty.h \
 ../Board/../Objects/Patch.h ../Board/../Objects/Hotfix.h \
 ../Board/../IOLoaders/Reader.h

