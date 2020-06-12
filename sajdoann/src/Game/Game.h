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
#include "State.enum"
#include "ScoreCounter.h"
#include "Movement/Movement.h"
#include "VirusWave.h"
#include "GameConstants.h"
class Interface;

using namespace std;

class Game {
    State gameState = State::WELCOME;
    ResultEnum gameResult = ResultEnum::UNKNOWN;
    ScoreCounter scoreCounter;
    Board gameBoard;
    Movement movement;
    map<char, Patch *> patches;
    map<char, Virus *> viruses;

    int ram = RAM_CONSTANT;        //TODO: zapojit do třídy
    int level = 0;
    int money = 50;

public:
    Game();

    ~Game();

    State GameState() const { return gameState; }

    void GameState(State state) { this->gameState = state; }

    ResultEnum GameResult() const { return gameResult; }

    void GameResult(ResultEnum result) { this->gameResult = result; }


    Board &GameBoard() { return gameBoard; }

    bool OutOfGameBoard(const Coords &coords) const { return gameBoard.OutOfBoard(coords); }

    map<char, Virus *> Viruses() const { return viruses; }

    map<char, Patch *> Patches() const { return patches; }


    void LoadGame(const string &directoryPath);

    void SaveGame(const string &folderName);

    void InsertPatch(const char patchType, const Coords &coords);

    bool isPatch(char PatchName);

    Patch &getPatch(const char c) const;


    //TODO: implement
    bool MoveLoop(Interface anInterface);

    VirusWave *createVirusWave();
};



