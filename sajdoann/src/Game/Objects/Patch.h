/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <iostream>
#include <iomanip>
#include "ObjectWithMoveAttributes.h"
#include "Hotfix.h"
class Board;

using namespace std;

/**
 * patch is an Object that has name, type, price and range
 * In the FireWall game it can be placed on Board
 * It shoots hotfixes
 */
class Patch : public ObjectWithMoveAttributes {
protected:
    int price = 10;

public:
    Patch() noexcept = default;

    Patch(char name, int price, MovementType movementType, MovementDirection movementDirection) noexcept
            : ObjectWithMoveAttributes(name, movementType, movementDirection), price(price) {}

    ~Patch() override = default;

    Object *Clone() const override { return new Patch(name, price, movementType, movementDirection); }

    Patch(Patch &patch);


    Patch &operator=(const Patch &patch);

    /** gets the price of the patch */
    int Price() const { return price; }

    /** returns false because patch is not a moving object */
    bool isMovingObject() const override { return false; }

    /** returns false because patch is not empty object */
    bool isEmpty() const override { return false; }

    /** returns false because patch is not a virus*/
    virtual bool isVirus() const override { return false; };

    /** returns true because it is a patch*/
    virtual bool isPatch() const override { return true; };

    /** returns true if patch can shoot, if movement none -> false */
    virtual bool canShoot() const { return movementType != MovementType::NONE; }

    /** if can shoot it shoots hotfix and places it on board if strategy exec move conditions are met (it can be placed there) */
    int Attack(Board *newBoard, Board &oldBoard, Coords startCoords) override;

    /**
     * shoots hotfix
     * @return hotfix that was shooted
     */
    Hotfix ShootHotfix() {
        return Hotfix('*', movementType, movementDirection);
    }

    /** gets patch atributes from istream */
    friend istream &operator>>(istream &in, Patch &patch);

    /** loads patch */
    istream &LoadObject(istream &is) override;

    /** prints all available information for patches */
    ostream &PrintInfo(ostream &out) const override;


    /** prints just the name representation of object */
    ostream &SaveObject(ostream &os) override;

};



