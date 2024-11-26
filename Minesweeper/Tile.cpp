#include "Tile.h"
Tile::Tile(int xcoord, int ycoord) {
    hiddenTile.loadFromFile("files/images/tile_hidden.png");
    revealedTileTexture.loadFromFile("files/images/tile_revealed.png");
    mineTexture.loadFromFile("files/images/mine.png");
    flagTexture.loadFromFile("files/images/flag.png");
    numberOneTexture.loadFromFile("files/images/number_1.png");
    numberTwoTexture.loadFromFile("files/images/number_2.png");
    numberThreeTexture.loadFromFile("files/images/number_3.png");
    numberFourTexture.loadFromFile("files/images/number_4.png");
    numberFiveTexture.loadFromFile("files/images/number_5.png");
    numberSixTexture.loadFromFile("files/images/number_6.png");
    numberSevenTexture.loadFromFile("files/images/number_7.png");
    numberEightTexture.loadFromFile("files/images/number_8.png");
    this->surroundingMines = 0;
    this->sprite.setPosition(xcoord * 32, ycoord * 32);
    is_mine = false;
    is_revealed = false;
    is_flagged = false;
    is_enabled = true;}
void Tile::draw(RenderWindow &window, bool is_debugMode, bool is_paused, bool leaderBoard, bool loser, bool winner) {
    if (is_paused || (leaderBoard && !winner)) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        return;}
    if (is_flagged) {
        this->sprite.setTexture(hiddenTile);
        window.draw(this->sprite);
        this->sprite.setTexture(flagTexture);
        window.draw(this->sprite);
        return;}
    if (is_debugMode) {
        this->sprite.setTexture(hiddenTile);
        window.draw(this->sprite);
        if (is_mine) {
            this->sprite.setTexture(mineTexture);
            window.draw(this->sprite);}
        return;}
    if (is_revealed) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        if (is_mine) {
            this->sprite.setTexture(mineTexture);
            window.draw(this->sprite);
        } else {
            Texture* numberTexture = nullptr;
            switch (surroundingMines) {
                case 1: numberTexture = &numberOneTexture; break;
                case 2: numberTexture = &numberTwoTexture; break;
                case 3: numberTexture = &numberThreeTexture; break;
                case 4: numberTexture = &numberFourTexture; break;
                case 5: numberTexture = &numberFiveTexture; break;
                case 6: numberTexture = &numberSixTexture; break;
                case 7: numberTexture = &numberSevenTexture; break;
                case 8: numberTexture = &numberEightTexture; break;}
            if (numberTexture) {
                this->sprite.setTexture(*numberTexture);
                window.draw(this->sprite);}}
        return;}
    this->sprite.setTexture(hiddenTile);
    window.draw(this->sprite);}
void Tile::togFlag() {
    if (this->is_flagged) {
        this->is_flagged = false;} else {
        this->is_flagged = true;}}
