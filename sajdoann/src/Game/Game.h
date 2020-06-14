/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 4/30/2020
*/

#pragma once

#include <map>

#include "Board/Board.h"
#include "Objects/Patch.h"
#include "IOLoaders/Reader.h"
#include "ResultEnum.h"
#include "State_Enum.h"
#include "ScoreCounter.h"
#include "Movement/Movement.h"
#include "VirusWave.h"
#include "GameConstants.h"
class Interface;

using namespace std;

class Game {
    State gameState = State::MENU;
    ResultEnum gameResult = ResultEnum::UNKNOWN;

    Board gameBoard;
    Movement movement;
    map<char, Patch *> patches;
    map<char, Virus *> viruses;

    Counter scoreCounter;

    void free_patches_and_viruses();

    void read_patches_and_viruses(const string &directoryPath);

    void read_gameBoard(const string &directoryPath);

    void read_score(const string &directoryPath);

    void save_patches_and_viruses(const string &directoryPath) const;

    void save_gameBoard(const string &directoryPath);

    void save_ctr(const string &directoryPath);


public:
    Game();

    ~Game();

    State GameState() const { return gameState; }

    void GameState(State state) { this->gameState = state; }

    ResultEnum GameResult() const { return gameResult; }

    Counter &getScoreCounter() { return scoreCounter; }

    bool BuyPatch(int cost) {
        return scoreCounter.Buy(cost);
    }

    void GameResult(ResultEnum result) { this->gameResult = result; }


    Board &GameBoard() { return gameBoard; }

    bool OutOfGameBoard(const Coords &coords) const { return gameBoard.OutOfBoard(coords); }

    map<char, Virus *> Viruses() const { return viruses; }

    map<char, Patch *> Patches() const { return patches; }


    void LoadGame(const string &directoryPath);

    void SaveGame(const string &directoryPath);

    void InsertPatch(const char patchType, const Coords &coords);

    bool isPatch(char PatchName);

    bool isVirus(char VirusName);

    Patch &getPatch(const char c) const;

    Virus &getVirus(const char c) const;

    bool MoveLoop(Interface &anInterface);

};



