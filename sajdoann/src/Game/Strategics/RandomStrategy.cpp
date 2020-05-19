/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/19/2020
*/

#include <random>
#include "RandomStrategy.h"
#include "../Board/Board.h"

/*
Coords * RandomStrategy::Move(Board *oldBoard, Board &newBoard, const Coords &startCoords) {
    Coords targetCoords;

    //taken from https://en.cppreference.com/w/cpp/numeric/random
    random_device r;
    default_random_engine e1(r());
    uniform_int_distribution<int> dist_tri(-1,1);
    uniform_int_distribution<int> dist_bin(0,1);

    if(movementDirection == MovementDirection::RIGHT){
        targetCoords = Coords(dist_bin(e1), dist_tri(e1));
        //target offset is 00 -> would not move -> add 1
        if(targetCoords == Coords()){
            targetCoords.setCoords(targetCoords.X()+1, targetCoords.Y());
        }
    }

    targetCoords.setCoords(targetCoords.X() + startCoords.X(), targetCoords.Y() + startCoords.Y());


    if(!targetCoords.canStep(oldBoard)){
        return Coords(-1,-1);
    }
    Object *o = newBoard.At(targetCoords);

    //hotfix condition -> if just inserted dont move
    if (!o->isVirus() && o->isMovingObject()) {
        Hotfix *hotfix = (Hotfix *) o;
        hotfix->setInserted(true);
        return true;
    }

    //there is patch on target position
    if (!o->isEmpty() && !o->isMovingObject()) {
        return true;
    }

    newBoard.InsertObject(*((Hotfix *) oldBoard->At(startCoords)), targetCoords);

    return true;
}
*/