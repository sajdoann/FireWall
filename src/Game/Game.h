/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <map>

#include "../Board/Board.h"
#include "../Objects/Patch.h"
#include "../Readers/Reader.h"
#include "State.enum"

using namespace std;

class Game {
    State gameState = State::WELCOME;
    /*GameResult gameResult;
    //ScoreCounter scoreCounter;*/
    Board gameBoard;
    map< char, Patch *> patches;
    map<char, Virus *> viruses;

public:
    Game() {
        Reader patchReader("../tests/patches.txt");
        patches = patchReader.ReadStillObjects<Patch>();

        Reader virusReader("../tests/viruses.txt");
        viruses = virusReader.ReadStillObjects<Virus>();

        Reader boardReader("../tests/board.txt");
        int maxX, maxY;
        set<Coords> coords = boardReader.ReadBoard(maxX, maxY);
        Board b(maxX, maxY, coords);
        gameBoard = b;
    }

    State GameState() const {return gameState;}
    void GameState(State state){ this->gameState = state; }

    Board & GameBoard(){return gameBoard;}
    bool OutOfGameBoard(const Coords & coords) const {return gameBoard.OutOfBoard(coords);}


    void InsertPatch(const char patchType, const Coords & coords){
        auto it = patches.find(patchType);
        gameBoard.InsertPatch((it->second), coords);
    }

    bool isPatch(char PatchName){
        return patches.find(PatchName) != patches.end();
    }

};



