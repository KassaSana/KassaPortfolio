
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Tile{
    Texture flagTexture;
    Texture revealedTileTexture;
    Texture mineTexture;
    Texture numberOneTexture;
    Texture numberTwoTexture;
    Texture numberThreeTexture;
    Texture numberFourTexture;
    Texture numberFiveTexture;
    Texture numberSixTexture;
    Texture numberSevenTexture;
    Texture numberEightTexture;
    Texture hiddenTile;
public:
    Sprite sprite;
    vector<Tile*> vectorOfNeighborTilePointers;
    bool is_mine;
    bool is_flagged;
    bool is_enabled;
    bool is_revealed;
    int surroundingMines;
    Tile(int xcoord, int ycoord);
    void draw(RenderWindow& window, bool is_debugMode, bool is_paused,bool leaderBoard, bool loser, bool winner);
    void togFlag();
};
