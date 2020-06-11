/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/11/2020
*/

#pragma once
using namespace std;

#include "../Movement/MovementType.h"
#include "../Movement/MovementDirection.h"
#include "Object.h"

class ObjectWithMoveAttributes : public Object {
protected:
    MovementType movementType = MovementType::STRAIGHT;
    MovementDirection movementDirection = MovementDirection::LEFT;

public:
    ObjectWithMoveAttributes() = default;

    ObjectWithMoveAttributes(char name, MovementType movementType, MovementDirection movementDirection) :
            Object(name), movementType(movementType), movementDirection(movementDirection) {}

    ObjectWithMoveAttributes(char name, ObjectWithMoveAttributes &o) : Object(name) {
        name = o.name;
        movementType = o.movementType;
        movementDirection = o.movementDirection;
    }

    virtual ~ObjectWithMoveAttributes() = default;

    virtual int Attack(Board *newBoard, Board &oldBoard, Coords startCoords) = 0;

    virtual ostream &SaveObject(ostream &out) = 0;

    virtual istream &LoadObject(istream &in) = 0;

    virtual ostream &PrintInfo(ostream &out) const = 0;

    virtual bool isMovingObject() const = 0;

    virtual bool isEmpty() const { return false; };

    virtual bool isVirus() const = 0;

    virtual bool isPatch() const = 0;

    istream &MovementFromIn(istream &in, MovementType &value) {
        string a;
        in >> a;
        if (a == "STRAIGHT")
            value = MovementType::STRAIGHT;
        else if (a == "FRONT")
            value = MovementType::FRONT;
        else if (a == "SHORTEST")
            value = MovementType::SHORTEST;
        else if (a == "RAND")
            value = MovementType::RAND;
        else if (a == "NONE")
            value = MovementType::NONE;
        else
            in.setstate(std::ios_base::failbit);
        return in;
    }

    ostream &MovementToOut(ostream &out, const MovementType &value) const {
        string s;
        switch (value) {
            case MovementType::STRAIGHT:
                s = "STRAIGHT";
                break;
            case MovementType::FRONT:
                s = "FRONT";
                break;
            case MovementType::SHORTEST:
                s = "SHORTEST";
                break;
            case MovementType::RAND:
                s = "RAND";
                break;
            case MovementType::NONE:
                s = "NONE";
                break;
        }
        return out << s;
    }

    istream &DirectionFromIn(istream &in, MovementDirection &value) {
        //RIGHT, UP, DOWN, OTHER
        string a;
        in >> a;
        if (a == "RIGHT")
            value = MovementDirection::RIGHT;
        else if (a == "UP")
            value = MovementDirection::UP;
        else if (a == "DOWN")
            value = MovementDirection::DOWN;
        else if (a == "LEFT")
            value = MovementDirection::LEFT;
        else if (a == "DIAGONAL_U")
            value = MovementDirection::DIAGONAL_U;
        else if (a == "DIAGONAL_D")
            value = MovementDirection::DIAGONAL_D;
        else
            in.setstate(std::ios_base::failbit);
        return in;
    }

    ostream &DirectionsToOut(ostream &out, const MovementDirection &value) const {
        string s;
        switch (value) {
            case MovementDirection::RIGHT:
                s = "RIGHT";
                break;
            case MovementDirection::UP:
                s = "UP";
                break;
            case MovementDirection::DOWN:
                s = "DOWN";
                break;
            case MovementDirection::LEFT:
                s = "LEFT";
                break;
            case MovementDirection::DIAGONAL_U:
                s = "DIAGONAL_U";
                break;
            case MovementDirection::DIAGONAL_D:
                s = "DIAGONAL_D";
                break;
        }
        return out << s;
    }


};

