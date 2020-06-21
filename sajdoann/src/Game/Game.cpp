/**
* @author Anna Sajdokova <sajdoann@fit.cvut.cz>
* @date 5/31/2020
*/

#include "Game.h"
#include "../Interface.h"
#include "IOLoaders/Writer.h"
#include <iostream>

Game::Game() : gameBoard(), scoreCounter(), virusGenerator() {
}

Game::~Game() {
    free_patches_and_viruses();
}

void Game::LoadGame(const string &directoryPath) {
    free_patches_and_viruses();
    read_patches_and_viruses(directoryPath);
    read_gameBoard(directoryPath);
    read_score(directoryPath);
    virusGenerator = VirusWave(scoreCounter.Level(), viruses);

}


void Game::free_patches_and_viruses() {
    if (!patches.empty()) {
        for (auto p : patches) {
            delete p.second;
            p.second = nullptr;
        }
    }
    if (!viruses.empty()) {
        for (auto v : viruses) {
            delete v.second;
            v.second = nullptr;
        }
    }
}

void Game::read_patches_and_viruses(const string &directoryPath) {
    Reader patchReader(directoryPath + "/patches.txt");
    patches = patchReader.ReadObjects<Patch>();

    Reader virusReader(directoryPath + "/viruses.txt");
    viruses = virusReader.ReadObjects<Virus>();
}

void Game::read_gameBoard(const string &directoryPath) {
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

void Game::read_score(const string &directoryPath) {
    Reader scoreReader(directoryPath + "/score.txt");
    scoreCounter = scoreReader.ReadScore();

}

void Game::InsertPatch(const char patchType, const Coords &coords) {
    auto it = patches.find(patchType);
    gameBoard.InsertPatch(*(it->second), coords);
}

bool Game::isPatch(char PatchName) {
    return patches.find(PatchName) != patches.end();
}

bool Game::isVirus(char VirusName) {
    return viruses.find(VirusName) != viruses.end();
}

Patch &Game::getPatch(const char c) const { return *patches.at(c); }

Virus &Game::getVirus(const char c) const { return *viruses.at(c); }



void Game::SaveGame(const string &directoryPath) {
    save_patches_and_viruses(directoryPath);
    save_gameBoard(directoryPath);
    save_ctr(directoryPath);
}

void Game::save_patches_and_viruses(const string &directoryPath) const {
    Writer patchWriter(directoryPath + "/patches.txt");
    patchWriter.writeObjectsFromMap(Patches());
    patchWriter.Close();

    Writer VirusWriter(directoryPath + "/viruses.txt");
    VirusWriter.writeObjectsFromMap(Viruses());
    VirusWriter.Close();
}

void Game::save_gameBoard(const string &directoryPath) {
    Writer BoardWriter(directoryPath + "/board.txt");
    BoardWriter.writeBoard(gameBoard);
    BoardWriter.Close();
}

void Game::save_ctr(const string &directoryPath) {
    Writer ctrWriter(directoryPath + "/score.txt");
    ctrWriter.writeCounter(scoreCounter);
    ctrWriter.Close();
}

int Game::MoveAll() {
    Board newBoard(gameBoard.MaxX(), gameBoard.MaxY());
    newBoard.AddAllPatches(&gameBoard);

    int virusPoints = 0;
    for (int i = 0; i < gameBoard.MaxX(); ++i) {
        for (int j = 0; j < gameBoard.MaxY(); ++j) {
            Object *object = (gameBoard)(i, j);
            Coords coords(i, j);
            virusPoints += object->Attack(&gameBoard, newBoard, coords);
        }
    }

    gameBoard = newBoard;
    return virusPoints;
}

void Game::GenerateAndPlaceViruses() {
    queue<pair<Virus *, Coords>> virusWave = virusGenerator.GeneateWave(gameBoard.MaxX(), gameBoard.MaxY());
    while (!virusWave.empty()) {
        pair<Virus *, Coords> a = virusWave.front();
        if (gameBoard.At(a.second)->isEmpty()) {
            gameBoard.InsertObject(*(a.first), a.second);
        }
        virusWave.pop();
    }
}


