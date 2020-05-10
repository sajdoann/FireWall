/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/7/2020
*/

#pragma once

#include <functional>
#include "Object.h"
#include "MovingObject.h"

using namespace std;

/**
 * moving object that is emited by patches
 * it travels on board till it encounters other object, then its destroyed (if encounters virus it takes its one live away)
 */
class Hotfix : public MovingObject {

    char name;

public:
    Hotfix();

    Hotfix(MovementType movementType, MovementDirection movementDirection);

    ~ Hotfix();

    ostream &PrintObject(ostream &os);

    ostream &PrintInfo(ostream &os);


};

