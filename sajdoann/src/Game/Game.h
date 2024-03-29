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
#include "StateEnum.h"
#include "ScoreCounter.h"
#include "VirusWave.h"
class Interface;

using namespace std;
/**
 * class that knows everything about game - its score, result, patches, viruses and board
 */
class Game {
    State gameState = State::MENU;
    ResultEnum gameResult = ResultEnum::UNKNOWN;

    Board gameBoard;
    map<char, Patch *> patches;
    map<char, Virus *> viruses;

    Counter scoreCounter;
    VirusWave virusGenerator;

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

    /** gets game state */
    State GameState() const { return gameState; }

    /** sets game state */
    void GameState(State state) { this->gameState = state; }

    /** returns game result  */
    ResultEnum GameResult() const { return gameResult; }

    VirusWave VirusGenerator() const { return virusGenerator; }

    /** gets score counter */
    Counter &getScoreCounter() { return scoreCounter; }

    /**
     * buys patch if enough money
     * @param cost - what is the price of the patch
     * @return
     */
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
     * moves all objects on the board by one step
     * creates new board, adds all patches, interates and adds all objects on moved(target) position
     * assigns board new board
     * @return how many viruses broke through the wall
     */
    int MoveAll();

    /**
     * generates and places viruses on board
     * during attack stage
     */
    void GenerateAndPlaceViruses();

};



