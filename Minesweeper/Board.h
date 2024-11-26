#pragma once
#include "Tile.h"

struct Board {
    int flagsToPlace;
    vector<vector<Tile*>*> twoDimensionalVectorOfBoardPointer;
    bool leaderBoard;
    int rows;
    int columns;
    bool loser;
    bool is_debugMode;
    int tiles;
    bool is_paused;
    int mineCount;
    bool winner;

    Board();
    void draw(RenderWindow& window);
    void togDebugMode();
    void togPauseMode();
    void enableAllTiles();
    void reveal(RenderWindow& window,Tile* tile);
    bool checkIfWinner();
    void clear();
    void togLeaderBoard();
    void disableAllTiles();

};
