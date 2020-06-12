/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/31/2020
*/

#include "Game.h"
#include "IOLoaders/Writer.h"
#include <iostream>
#include <dirent.h>
#include "GameConstants.h"

void Game::LoadGame(const string &directoryPath) {
    //TODO: invalid inputs
    Reader patchReader(directoryPath + "/patches.txt");
    patches = patchReader.ReadStillObjects<Patch>();

    Reader virusReader(directoryPath + "/viruses.txt");
    viruses = virusReader.ReadStillObjects<Virus>();

    Reader boardReader(directoryPath + "/board.txt");
    int maxX, maxY;

    map<Coords, char> coords = boardReader.ReadBoard(maxX, maxY);
    map<Coords, Patch *> patchesMap;
    for (auto c : coords) {
        Patch *p;
        if (isPatch(c.second)) {
            Patch cp(getPatch(c.second));
            p = new Patch(cp);
        } else
            throw invalid_argument("No such patch exists. Patch name: " + c.second);
        patchesMap.insert({c.first, p});
    }
    Board b(maxX, maxY, patchesMap);

    for (auto &a : patchesMap) {
        delete a.second;
        a.second = nullptr;
    }
    gameBoard = b;
}

Game::Game() : scoreCounter(ScoreCounter()), gameBoard(), movement(&gameBoard) {
}

Game::~Game() {
    for (auto p : patches) {
        delete p.second;
    }
    for (auto v : viruses) {
        delete v.second;
    }
}

void Game::InsertPatch(const char patchType, const Coords &coords) {
    auto it = patches.find(patchType);
    gameBoard.InsertPatch(*(it->second), coords);
}

bool Game::isPatch(char PatchName) {
    return patches.find(PatchName) != patches.end();
}

Patch &Game::getPatch(const char c) const { return *patches.at(c); }

bool Game::MoveLoop(Interface anInterface) {
    VirusWave virusWave(level, viruses);

    int virusPoints = 0;
    for (int i = 0; i < MOVEMENT_LOOP_MAX; ++i) {
        virusPoints = 0;
        queue<pair<Virus *, Coords>> vw = virusWave.GeneateWave(gameBoard.MaxX(), gameBoard.MaxY());
        while (!vw.empty()) {
            pair<Virus *, Coords> a = vw.front();
            if (gameBoard.At(a.second)->isEmpty()) {
                gameBoard.InsertObject(*(a.first), a.second);
            }
            vw.pop();
            anInterface.PrintBoardPrep(gameBoard);
        }

        virusPoints += movement.MoveAll();
        ram -= virusPoints;
        if (ram < 0) {
            GameResult(LOSE);
            gameState = State::END;
            break;
        }

        anInterface.PrintBoardPrep(gameBoard);
        cout << "ram: " << ram << endl;
        this_thread::sleep_for(0.3s);
    }
    gameBoard.ClearButPatches();
    ++level;    // game goes to bigger lvl
}

void Game::SaveGame(const string &folderName) {


    Writer patchWriter(folderName + "/patches.txt");
    patchWriter.getHeading(*(Patches().begin()->second));
    patchWriter.writeStillObjectsFromMap(Patches());
    patchWriter.Close();

    Writer VirusWriter(folderName + "/viruses.txt");
    VirusWriter.getHeading(*(Viruses().begin()->second));
    VirusWriter.writeStillObjectsFromMap(Viruses());
    VirusWriter.Close();

    Writer GameWriter(folderName + "/board.txt");
    GameWriter.writeBoard(gameBoard);
    GameWriter.Close();
}

