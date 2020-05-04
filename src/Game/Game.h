/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <map>

#include "../Board/Board.h"
#include "../Objects/Patch.h"
#include "../Readers/Reader.h"

using namespace std;

class Game {
    /*GameState gameState;
    GameResult gameResult;
    //ScoreCounter scoreCounter;*/
    Board board;
    map< char, Patch > patches;

public:
    Game() : board( Board(5,5)){
        Reader reader("../tests/towers.txt");
        patches =  reader.ReadPatches();
    }

    void InsertPatch(const char patchType, const Coords & coords){
        auto it = patches.find(patchType);
        board.InsertPatch(&(it->second), coords);
    }

};



