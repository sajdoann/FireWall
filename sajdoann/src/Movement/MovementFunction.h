/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include "../Objects/Coords.h"

/**
 *
 */
class MovementFunction {
    bool StraightMovementHotfix(const Coords & actualCoords, Coords & futureCoords);
    bool StraightMovementVirus(const Coords & actualCoords, Coords & futureCoords);
    bool seeFrontMovement(const Coords & actualCoords, Coords & futureCoords);
    bool shortestRouteMovement(const Coords & actualCoords, Coords & futureCoords);
};

