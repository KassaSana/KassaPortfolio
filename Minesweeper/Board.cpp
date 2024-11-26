#include "Board.h"
#include <random>
#include <fstream>
mt19937 random_mt;

int Random(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);}
Board::Board() {
    // read config file
    fstream boardConfig("files/board_config.cfg");
    string columnInfoString;
    getline(boardConfig, columnInfoString);
    this->columns = stoi(columnInfoString);
    string rowInfoString;
    getline(boardConfig, rowInfoString);
    this->rows = stoi(rowInfoString);
    this->tiles = (this->rows) * (this->columns);
    string mineCountInfoString;
    getline(boardConfig, mineCountInfoString);
    this->mineCount = stoi(mineCountInfoString);
    this->flagsToPlace = mineCount;
    this->is_debugMode = false;
    this->is_paused = false;
    this->leaderBoard = false;
    this->loser = false;
    this->winner = false;
    for (unsigned i = 0; i < rows; i++) {
        vector<Tile*>* currRow = new vector<Tile*>;
        for (unsigned j = 0; j < columns; j++) {
            Tile* tempPointer = new Tile(j, i);
            currRow->push_back(tempPointer);}
        twoDimensionalVectorOfBoardPointer.push_back(currRow);}
    for (int i = 0; i < this->mineCount; i++) {
        int randomRow = Random(0, rows - 1);
        int randomColumn = Random(0, columns - 1);
        if (twoDimensionalVectorOfBoardPointer.at(randomRow)->at(randomColumn)->is_mine) {
            i--;
        } else {
            twoDimensionalVectorOfBoardPointer.at(randomRow)->at(randomColumn)->is_mine = true;}}
    for (int i = 0; i < twoDimensionalVectorOfBoardPointer.size(); i++) {
        for (int j = 0; j < twoDimensionalVectorOfBoardPointer.at(i)->size(); j++) {
            if (j - 1 >= 0)
                twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.push_back(twoDimensionalVectorOfBoardPointer.at(i)->at(j - 1));
            if ((i - 1 >= 0) && (j - 1 >= 0))
                twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.push_back(twoDimensionalVectorOfBoardPointer.at(i - 1)->at(j - 1));
            if (i - 1 >= 0)
                twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.push_back(twoDimensionalVectorOfBoardPointer.at(i - 1)->at(j));
            if ((i - 1 >= 0) && (j + 1 <= columns - 1))
                twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.push_back(twoDimensionalVectorOfBoardPointer.at(i - 1)->at(j + 1));
            if (j + 1 <= columns - 1)
                twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.push_back(twoDimensionalVectorOfBoardPointer.at(i)->at(j + 1));
            if ((i + 1 <= rows - 1) && (j + 1 <= columns - 1))
                twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.push_back(twoDimensionalVectorOfBoardPointer.at(i + 1)->at(j + 1));
            if (i + 1 <= rows - 1)
                twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.push_back(twoDimensionalVectorOfBoardPointer.at(i + 1)->at(j));
            if ((i + 1 <= rows - 1) && (j - 1 >= 0))
                twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.push_back(twoDimensionalVectorOfBoardPointer.at(i + 1)->at(j - 1));
            if (!twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_mine) {
                for (unsigned int k = 0; k < twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.size(); k++) {
                    if (twoDimensionalVectorOfBoardPointer.at(i)->at(j)->vectorOfNeighborTilePointers.at(k)->is_mine)
                        twoDimensionalVectorOfBoardPointer.at(i)->at(j)->surroundingMines++;}}}}}
void Board::draw(RenderWindow& window) {
    for (unsigned i = 0; i < twoDimensionalVectorOfBoardPointer.size(); i++) {
        for (unsigned j = 0; j < twoDimensionalVectorOfBoardPointer.at(i)->size(); j++) {
            twoDimensionalVectorOfBoardPointer.at(i)->at(j)->draw(window, this->is_debugMode, this->is_paused, this->leaderBoard, this->loser, this->winner);}}}
void Board::togDebugMode() {
    is_debugMode = !is_debugMode;}
void Board::togPauseMode() {
    is_paused = !is_paused;}
bool Board::checkIfWinner() {
    short count = 0;
    for (unsigned i = 0; i < twoDimensionalVectorOfBoardPointer.size(); i++) {
        for (unsigned j = 0; j < twoDimensionalVectorOfBoardPointer.at(i)->size(); j++) {
            if (!twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_mine && twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_revealed) {
                count++;
                if (count == (tiles - mineCount))
                    return true;}}}return false;}
void Board::enableAllTiles() {
    for (unsigned i = 0; i < twoDimensionalVectorOfBoardPointer.size(); i++) {
        for (unsigned j = 0; j < twoDimensionalVectorOfBoardPointer.at(i)->size(); j++) {
            twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_enabled = true;}}}
void Board::togLeaderBoard() {
    leaderBoard = !leaderBoard;}
void Board::disableAllTiles() {
    for (unsigned i = 0; i < twoDimensionalVectorOfBoardPointer.size(); i++) {
        for (unsigned j = 0; j < twoDimensionalVectorOfBoardPointer.at(i)->size(); j++) {
            twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_enabled = false;}}}
void Board::reveal(RenderWindow& window, Tile* tile) {
    if (tile->is_flagged) return;
    tile->is_revealed = true;
    if (tile->surroundingMines == 0 && tile->is_enabled) {
        for (unsigned int i = 0; i < tile->vectorOfNeighborTilePointers.size(); i++) {
            if (!tile->vectorOfNeighborTilePointers.at(i)->is_revealed && tile->vectorOfNeighborTilePointers.at(i)->is_enabled)
                reveal(window, tile->vectorOfNeighborTilePointers.at(i));}}}
void Board::clear() {
    for (unsigned i = 0; i < twoDimensionalVectorOfBoardPointer.size(); i++) {
        vector<Tile*>* currRow = twoDimensionalVectorOfBoardPointer.at(i);
        for (unsigned j = 0; j < currRow->size(); j++) {
            delete currRow->at(j);
        }delete currRow;}}
