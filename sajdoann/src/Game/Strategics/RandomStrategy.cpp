/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/19/2020
*/

#include <random>
#include "RandomStrategy.h"
#include "../Board/Board.h"


Coords *RandomStrategy::getTargetCoords(Board *oldBoard, Board &newBoard, const Coords &startCoords) {
    Coords *targetCoords;

    //taken from https://en.cppreference.com/w/cpp/numeric/random
    random_device r;
    default_random_engine e1(r());
    uniform_int_distribution<int> dist_tri(-1, 1);
    uniform_int_distribution<int> dist_bin(-1, 0);

    if (movementDirection == MovementDirection::LEFT) {
        targetCoords = new Coords(dist_bin(e1), dist_tri(e1));
        //target offset is 00 -> would not move -> add 1
        if (*targetCoords == Coords()) {
            targetCoords->setCoords(targetCoords->X(), targetCoords->Y() - 1);
        }
    } else if (movementDirection == MovementDirection::RIGHT) {
        targetCoords = new Coords(dist_bin(e1) + 1, dist_tri(e1));
        if (*targetCoords == Coords()) {
            targetCoords->setCoords(targetCoords->X(), targetCoords->Y() + 1);
        }

    }

    targetCoords->setCoords(targetCoords->X() + startCoords.X(), targetCoords->Y() + startCoords.Y());
    return targetCoords;
}
