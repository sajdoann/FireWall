/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/11/2020
*/

#pragma once

#include <queue>
#include <vector>
#include "Objects/Virus.h"
#include <cmath>
#include <random>

using namespace std;

/**
 * creates virus wave mainly its generator
 */
class VirusWave {
private:
    int level = 0;
    vector<Virus *> virusQueue;
    default_random_engine e1 = CreateDevice();


    int MyRand(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(e1);
    }

    int CountMax() {
        //todo: alter
        if (level < 3) return 1;
        return 1;
    }

    default_random_engine CreateDevice() {
        random_device r;
        default_random_engine e1(r());
        return e1;
    }

public:
    //no need to free viruses - it destructs in Game viruses map
    ~VirusWave() = default;

    VirusWave() = default;

    VirusWave(int level, map<char, Virus *> viruses) : level(level) {
        for (auto i = viruses.begin(); i != viruses.end(); ++i) {
            virusQueue.push_back(i->second);
        }
    }

    /**
     * generates next wave
     * @param maxX - board maxX
     * @param maxY - board maxY
     * @return generated vawe for thhis round
     */
    queue<pair<Virus *, Coords >> GeneateWave(int maxX, int maxY) {
        queue<pair<Virus *, Coords >> wave;
        int max = CountMax();

        int waveCount = MyRand(0, max);
        uniform_int_distribution<int> distVirusType(0, virusQueue.size() - 1);
        uniform_int_distribution<int> distCoords(0, maxX - 1);

        for (int i = 0; i < waveCount; ++i) {
            int virusType = MyRand(0, virusQueue.size() - 1);
            int coordsX = MyRand(0, maxX - 1);
            wave.push({virusQueue[virusType], Coords(coordsX, maxY - 1)});
        }

        return wave;
    }

};

