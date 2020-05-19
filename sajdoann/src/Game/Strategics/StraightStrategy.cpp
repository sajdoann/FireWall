/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/14/2020
*/

#include "StraightStrategy.h"
#include "../Board/Board.h"

Coords *StraightStrategy::Move(Board *oldBoard, Board &newBoard, const Coords &startCoords) {
    //Coords targetCoords(startCoords.X(), startCoords.Y() + 1);
    Coords *targetCoords = getMovedCoords(startCoords);
    return targetCoords;
}
