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
/**
 * class that knows everything about game - its score, result, patches, viruses and board
 */
class Game {
    State gameState = State::MENU;
    ResultEnum gameResult = ResultEnum::UNKNOWN;

    Board gameBoard;
    Movement movement;
    map<char, Patch *> patches;
    map<char, Virus *> viruses;

    Counter scoreCounter;

    /** free patches and viruses */
    void free_patches_and_viruses();

    /** reades patches and viruses
     * @param directoryPath
     */
    void read_patches_and_viruses(const string &directoryPath);

    /** reads game board
     * @param directoryPath
     */
    void read_gameBoard(const string &directoryPath);

    /** reads score
     * @param directoryPath
     */
    void read_score(const string &directoryPath);

    /** saves patches and viruses
     * @param directoryPath
     */
    void save_patches_and_viruses(const string &directoryPath) const;

    /** saves game board
     * @param directoryPath
     */
    void save_gameBoard(const string &directoryPath);

    /** saves counter
     * @param directoryPath
     */
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

    /** finds out if coords are out of board
     * @param coords
     * @return true - they are out of board, alse false
     */
    bool OutOfGameBoard(const Coords &coords) const { return gameBoard.OutOfBoard(coords); }

    map<char, Virus *> Viruses() const { return viruses; }

    map<char, Patch *> Patches() const { return patches; }

    /**
     * loads game from files in directory
     * @param directoryPath - path to directory
     */
    void LoadGame(const string &directoryPath);

    /**
     * saves game to directoru
     * @param directoryPath - path to directory
     */
    void SaveGame(const string &directoryPath);

    /**
     * inserts patch to coords
     * @param patchType
     * @param coords
     */
    void InsertPatch(const char patchType, const Coords &coords);

    /**
     * checks with Patches if its a patch
     * @param PatchName
     * @return true - its a patch name, alse false
     */
    bool isPatch(char PatchName);

    /**
     * checks with Viruses if its a patch
     * @param VirusName
     * @return true - its a virus name, alse false
     */
    bool isVirus(char VirusName);

    /**
     * from Patches map gets patch by its name
     * @param c - char that represents the patch
     * @return
     */
    Patch &getPatch(const char c) const;

    /**
     * from Viruses map gets patch by its name
     * @param c - char that represents the virus
     * @return
     */
    Virus &getVirus(const char c) const;

    /**
     * creates wave of viruses for the attack, moves with the objects on board for certain amount of time
     * @param anInterface
     */
    void MoveLoop(Interface &anInterface);

};



