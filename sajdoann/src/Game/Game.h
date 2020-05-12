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
    ResultEnum gameResult = ResultEnum::UNKNOWN;
    ScoreCounter scoreCounter;
    Board gameBoard;
    Movement movement;
    map<char, Patch *> patches;
    map<char, Virus *> viruses;

    int ram = 0;        //TODO: zapojit do třídy

public:
    Game() : scoreCounter(ScoreCounter()), gameBoard(), movement(&gameBoard) {
        //TODO: invalid inputs
        Reader patchReader("../sajdoann/Data/patches.txt");
        patches = patchReader.ReadStillObjects<Patch>();

        Reader virusReader("../sajdoann/Data/viruses.txt");
        viruses = virusReader.ReadStillObjects<Virus>();

        Reader boardReader("../sajdoann/Data/board.txt");
        int maxX, maxY;

        map<Coords, char> coords = boardReader.ReadBoard(maxX, maxY);
        map<Coords, Patch *> patchesMap;
        for (auto c : coords) {
            Patch *p;
            if (isPatch(c.second))
                p = new Patch(getPatch(c.second));
            else throw runtime_error("No such patch exixts. Patch name: " + c.second);
            patchesMap.insert({c.first, p});
        }
        Board b(maxX, maxY, patchesMap);
        gameBoard = b;
    }

    ~Game() {
        for (auto p : patches) {
            delete p.second;
        }
        for (auto v : viruses) {
            delete v.second;
        }
    }

    State GameState() const { return gameState; }

    void GameState(State state) { this->gameState = state; }

    ResultEnum GameResult() const { return gameResult; }

    void GameResult(ResultEnum result) { this->gameResult = result; }


    Board &GameBoard() { return gameBoard; }

    bool OutOfGameBoard(const Coords &coords) const { return gameBoard.OutOfBoard(coords); }

    map<char, Virus *> Viruses() const { return viruses; }

    map<char, Patch *> Patches() const { return patches; }

    void InsertPatch(const char patchType, const Coords &coords) {
        auto it = patches.find(patchType);
        gameBoard.InsertPatch(*(it->second), coords);
    }

    bool isPatch(char PatchName) {
        return patches.find(PatchName) != patches.end();
    }

    Patch &getPatch(const char c) const { return *patches.at(c); }


    //TODO: implement
    bool MoveLoop() {

        movement.MoveAll();
    }

};



