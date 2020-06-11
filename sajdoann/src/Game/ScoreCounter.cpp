/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 6/10/2020
*/

#include "ScoreCounter.h"


void ScoreCounter::setNumberOfViruses(const int &numberOfViruses) { this->numberOfViruses = numberOfViruses; }

int ScoreCounter::NumberOfViruses() const { return numberOfViruses; }

int ScoreCounter::AcceptableLosses() const { return acceptableLosses; }

ResultEnum ScoreCounter::GetResult() const {
    return UNKNOWN;
}
