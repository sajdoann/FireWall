/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/11/2020
*/

#pragma once
using namespace std;

#include "../Movement/MovementType.h"
#include "../Movement/MovementDirection.h"
#include "Object.h"

/**
 * class that has all objects that need to have information about movement
 * the object but does not have to move itself
 * (fe patch needs info about hotfixes that it wants to shoot - not moving but needs movement info)
 * parent: object
 * children: patch, moving object(hotfix, virus)
 */
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

    /**
     * from stream finds out what movement type o with move atributs has
     * @param in - in stream
     * @param value - movement type
     * @return in stream
     */
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

    /**
     * from Movement type enum finds out what string to use when fe printing enum
     * @param out
     * @param value - string from this objects movement type, io parametr
     * @return ostream out
     */
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

    /**
     * loads from in stream value and finds out what mov. direction it is
     * @param in - in stream
     * @param value - mov. direction io parametr
     * @return in
     */
    istream &DirectionFromIn(istream &in, MovementDirection &value) {
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

    /**
     * from direction finds out whitch string to return
     * @param out
     * @param value
     * @return
     */
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

