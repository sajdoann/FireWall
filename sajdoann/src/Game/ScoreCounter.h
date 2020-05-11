/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/9/2020
*/

#pragma once

#include "ResultEnum.h"

/**
 * counts score based on how many viruses survive through the wall
 */
class ScoreCounter {
    int numberOfViruses = 0;
    int acceptableLosses = 0;
    int actualLoss = 0;

public:
    //TODO: implement this
    ScoreCounter() {};

    /**sets the number of viruses*/
    void setNumberOfViruses(const int &numberOfViruses) { this->numberOfViruses = numberOfViruses; }

    /**returns number of viruses */
    int NumberOfViruses() const { return numberOfViruses; }

    /**returns how many viruses can get through wall and its still a win*/
    int AcceptableLosses() const { return acceptableLosses; }

    /**counts the result */
    ResultEnum GetResult() const;


};

