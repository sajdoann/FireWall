/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/11/2020
*/

#pragma once

#include <deque>
#include <vector>
#include <algorithm>
#include "../Objects/Virus.h"

using namespace std;

class VirusWave {
private:
    int count;
    int difficulty;
    deque<Virus *> queue;

public:
    VirusWave(int count, int difficulty, vector<Virus *> viruses) : count(count), difficulty(difficulty) {
        sort(viruses.begin(), viruses.end(), [](Virus *a, Virus *b) {
            if (a->)
        })
    }

    //no free of viruses it destructs in Game viruses map
    ~VirusWave() = default;

};

