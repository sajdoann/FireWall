/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <map>

#include "../Board/Board.h"
#include "../Objects/Patch.h"
#include "../IOLoaders/Reader.h"
#include "ResultEnum.h"
#include "State.enum"
#include "ScoreCounter.h"
#include "../Movement/Movement.h"

using namespace std;

class Game {
    State gameState = State::WELCOME;
    ResultEnum gameResult = ResultEnum::WIN;
    ScoreCounter scoreCounter;
    Board gameBoard;
    Movement movement;
    map<char, Patch *> patches;
    map<char, Virus *> viruses;

public:
    Game() : scoreCounter(ScoreCounter()), gameBoard(), movement(&gameBoard)  {
        Reader patchReader("../Data/patches.txt");
        patches = patchReader.ReadStillObjects<Patch>();

        Reader virusReader("../Data/viruses.txt");
        viruses = virusReader.ReadStillObjects<Virus>();

        Reader boardReader("../Data/board.txt");
        int maxX, maxY;
        set<Coords> coords = boardReader.ReadBoard(maxX, maxY);
        Board b(maxX, maxY, coords);
        gameBoard = b;
    }

    State GameState() const { return gameState; }

    void GameState(State state) { this->gameState = state; }

    ResultEnum GameResult() const { return gameResult; }

    void GameResult(ResultEnum result) { this->gameResult = result; }


    Board &GameBoard() { return gameBoard; }

    bool OutOfGameBoard(const Coords &coords) const { return gameBoard.OutOfBoard(coords); }


    void InsertPatch(const char patchType, const Coords &coords) {
        auto it = patches.find(patchType);
        gameBoard.InsertPatch((it->second), coords);
    }

    bool isPatch(char PatchName) {
        return patches.find(PatchName) != patches.end();
    }

    bool MoveAll(){
        movement.MoveAll();
    }

};



