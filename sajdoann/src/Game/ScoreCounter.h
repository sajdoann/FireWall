/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include "ResultEnum.h"
#include "GameConstants.h"

/**
 * counts score based on how many viruses survive through the wall
 */
class ScoreCounter {
    ResultEnum gameResult = ResultEnum::UNKNOWN;
    int ram = RAM_CONSTANT;        //TODO: zapojit do třídy
    int ramStart = RAM_CONSTANT;
    int level = 0;
    int money = 50;


public:
    //TODO: implement this
    ScoreCounter() = default;

    /**sets the number of viruses*/
    void setNumberOfViruses(const int &numberOfViruses);

    /**returns number of viruses */
    int NumberOfViruses() const;

    /**returns how many viruses can get through wall and its still a win*/
    int AcceptableLosses() const;

    /**counts the result */
    ResultEnum GetResult() const;


};


