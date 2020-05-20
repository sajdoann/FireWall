/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/11/2020
*/

#pragma once

#include <queue>
#include <vector>
#include <algorithm>
#include "Objects/Virus.h"

using namespace std;

class VirusWave {
private:
    int count = 0;
    queue<Virus> virusQueue;

public:
    VirusWave(std::queue<Virus> viruses) : count(viruses.size()), virusQueue(viruses) {
    }

    void Insert(Virus &virus) {
        virusQueue.push(move(virus));
    }

    //no free of viruses it destructs in Game viruses map
    ~VirusWave() = default;

    VirusWave() = default;
};

