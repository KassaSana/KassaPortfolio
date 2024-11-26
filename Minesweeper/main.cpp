#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Stopwatch.h"
using namespace std;
using namespace sf;

struct Player {
    short timeInSec;
    string name;
};
void centerText(Text &text, float xcoord, float ycoord) {
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(Vector2f(xcoord, ycoord));}
Text createText(const string& textString, Font& font, short size, Color color, float xcoord, float ycoord) {
    Text text(textString, font, size);
    text.setFillColor(color);
    centerText(text, xcoord, ycoord);
    return text;}
int main() {
    Board gameBoard;
    int mainWindowWidth = gameBoard.columns * 32;
    int mainWindowHeight = gameBoard.rows * 32 + 100;
    int leaderboardWindowWidth = gameBoard.columns * 16;
    int leaderboardWindowHeight = gameBoard.rows * 16 + 50;
    Font font;
    if (!font.loadFromFile("files/font.ttf"))
        cout << "Failed to load font file!" << endl;
    String userInput;
    Text userName;
    RenderWindow welcomeWindow(VideoMode(mainWindowWidth, mainWindowHeight), "WELCOME");
    while (welcomeWindow.isOpen()) {
        Event event;
        Text welcomeText = createText("WELCOME TO MINESWEEPER!", font, 24, Color::White, mainWindowWidth / 2.0f, (mainWindowHeight / 2.0f) - 150);
        welcomeText.setStyle(Text::Bold | Text::Underlined);
        Text inputPromptText = createText("Enter your name:", font, 20, Color::White, mainWindowWidth / 2.0f, (mainWindowHeight / 2.0f) - 75);
        inputPromptText.setStyle(Text::Bold);
        while (welcomeWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                welcomeWindow.close();
                return 0;
            } else if (event.type == Event::TextEntered) {
                if (isalpha(event.text.unicode) && userInput.getSize() < 10) {
                    if (userInput.getSize() == 0) {
                        char temp = static_cast<char>(event.text.unicode);
                        temp = toupper(temp);
                        userInput += temp;
                    } else {
                        char temp = static_cast<char>(event.text.unicode);
                        temp = tolower(temp);
                        userInput += temp;
                    }
                    userName = createText(userInput + "|", font, 18, Color::Yellow, mainWindowWidth / 2.0f, (mainWindowHeight / 2.0f) - 45);
                    userName.setStyle(Text::Bold);
                }
            } else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && userInput.getSize() != 0) {
                welcomeWindow.close();
            } else if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace && userInput.getSize() > 0) {
                userInput.erase((userInput.getSize() - 1));
                userName = createText(userInput + "|", font, 18, Color::Yellow, mainWindowWidth / 2.0f, (mainWindowHeight / 2.0f) - 45);
                userName.setStyle(Text::Bold);}}
        welcomeWindow.clear(Color::Blue);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(inputPromptText);
        welcomeWindow.draw(userName);
        welcomeWindow.display();}
    Sprite faceSprite;
    faceSprite.setPosition((((gameBoard.columns) / 2) * 32) - 32, 32 * (gameBoard.rows + 0.5));
    Texture faceTexture;
    faceTexture.loadFromFile("files/images/face_happy.png");
    faceSprite.setTexture(faceTexture);
    Sprite debugSprite;
    debugSprite.setPosition(((gameBoard.columns) * 32) - 304, 32 * (gameBoard.rows + 0.5));
    Texture debugTexture;
    debugTexture.loadFromFile("files/images/debug.png");
    debugSprite.setTexture(debugTexture);
    bool debugButtonEnabled = true;
    Sprite pauseSprite;
    pauseSprite.setPosition(((gameBoard.columns) * 32) - 240, 32 * (gameBoard.rows + 0.5));
    Texture pauseTexture;
    pauseTexture.loadFromFile("files/images/pause.png");
    pauseSprite.setTexture(pauseTexture);
    bool pauseButtonEnabled = true;
    Sprite leaderboardSprite;
    leaderboardSprite.setPosition(((gameBoard.columns) * 32) - 176, 32 * (gameBoard.rows + 0.5));
    Texture leaderboardTexture;
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");
    leaderboardSprite.setTexture(leaderboardTexture);
    Sprite digitsSprite[11];
    Texture digitsTexture;
    digitsTexture.loadFromFile("files/images/digits.png");
    for (unsigned int i = 0; i < 11; i++) {
        digitsSprite[i].setTexture(digitsTexture);
        digitsSprite[i].setTextureRect(IntRect(i * 21, 0, 21, 32));}
    StopWatch gameClock; //start clock
    vector<Player> vectorOfActiveHighscores;
    vector<Player> vectorOfALLHighscoreFileLines;
    int newWinnerPosition = -1;
    string tempLine;
    fstream highscoreFile("files/leaderboard.txt", ios_base::in);
    while (getline(highscoreFile, tempLine)) {
        Player tempPlayer;
        stringstream ss(tempLine);
        string highscoreMinString;
        getline(ss, highscoreMinString, ':');
        int highScoreMin = stoi(highscoreMinString);
        string highscoreSecString;
        getline(ss, highscoreSecString, ',');
        int highScoreSec = stoi(highscoreSecString);
        highScoreSec += (highScoreMin * 60);
        tempPlayer.timeInSec = highScoreSec;
        getline(ss, tempPlayer.name);
        vectorOfALLHighscoreFileLines.push_back(tempPlayer);}
    highscoreFile.close();
    highscoreFile.open("files/leaderboard.txt", ios_base::in);
    for (unsigned int i = 0; i < 5 && getline(highscoreFile, tempLine); i++) {
        Player tempPlayer;
        stringstream ss(tempLine);
        string highscoreMinString;
        getline(ss, highscoreMinString, ':');
        int highScoreMin = stoi(highscoreMinString);
        string highscoreSecString;
        getline(ss, highscoreSecString, ',');
        int highScoreSec = stoi(highscoreSecString);
        highScoreSec += (highScoreMin * 60);
        tempPlayer.timeInSec = highScoreSec;
        getline(ss, tempPlayer.name);
        vectorOfActiveHighscores.push_back(tempPlayer);}
    highscoreFile.close();
    RenderWindow gameWindow(VideoMode(mainWindowWidth, mainWindowHeight), "Minesweeper");
    while (gameWindow.isOpen()) {
        gameWindow.clear(Color::White);
        gameBoard.draw(gameWindow);
        int currentUserMins = gameClock.getElapsedTime().asSeconds() / 60;
        int currentUserSecs = ((int)gameClock.getElapsedTime().asSeconds()) % 60;
        if (gameBoard.flagsToPlace < 0) {
            digitsSprite[10].setPosition(12, (32 * (gameBoard.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[10]);}
        if (gameBoard.flagsToPlace >= 0) {
            int mineCountHundredsDigit = gameBoard.flagsToPlace / 100;
            digitsSprite[mineCountHundredsDigit].setPosition(33, (32 * (gameBoard.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mineCountHundredsDigit]);
            int mineCountTensDigit = (gameBoard.flagsToPlace - (mineCountHundredsDigit * 100)) / 10;
            digitsSprite[mineCountTensDigit].setPosition(54, (32 * (gameBoard.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mineCountTensDigit]);
            int mineCountOnesDigit = gameBoard.flagsToPlace - (mineCountHundredsDigit * 100) - (mineCountTensDigit * 10);
            digitsSprite[mineCountOnesDigit].setPosition(75, (32 * (gameBoard.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mineCountOnesDigit]);
        } else if (gameBoard.flagsToPlace < 0) {
            gameBoard.flagsToPlace = abs(gameBoard.flagsToPlace);
            int mineCountHundredsDigit = gameBoard.flagsToPlace / 100;
            digitsSprite[mineCountHundredsDigit].setPosition(33, (32 * (gameBoard.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mineCountHundredsDigit]);
            int mineCountTensDigit = (gameBoard.flagsToPlace - (mineCountHundredsDigit * 100)) / 10;
            digitsSprite[mineCountTensDigit].setPosition(54, (32 * (gameBoard.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mineCountTensDigit]);
            int mineCountOnesDigit = gameBoard.flagsToPlace - (mineCountHundredsDigit * 100) - (mineCountTensDigit * 10);
            digitsSprite[mineCountOnesDigit].setPosition(75, (32 * (gameBoard.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mineCountOnesDigit]);
            gameBoard.flagsToPlace *= -1;}
        digitsSprite[currentUserMins / 10].setPosition((gameBoard.columns * 32) - 97, (32 * (gameBoard.rows + 0.5)) + 16);
        gameWindow.draw(digitsSprite[currentUserMins / 10]);
        digitsSprite[currentUserMins % 10].setPosition((gameBoard.columns * 32) - 76, (32 * (gameBoard.rows + 0.5)) + 16);
        gameWindow.draw(digitsSprite[currentUserMins % 10]);
        digitsSprite[currentUserSecs / 10].setPosition((gameBoard.columns * 32) - 54, (32 * (gameBoard.rows + 0.5)) + 16);
        gameWindow.draw(digitsSprite[currentUserSecs / 10]);
        digitsSprite[currentUserSecs % 10].setPosition((gameBoard.columns * 32) - 33, (32 * (gameBoard.rows + 0.5)) + 16);
        gameWindow.draw(digitsSprite[currentUserSecs % 10]);
        Event gameEvent;
        auto gameWindowClickPosition = Mouse::getPosition(gameWindow);
        auto gameWindowClick = gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow));
        gameWindow.draw(faceSprite);
        gameWindow.draw(debugSprite);
        gameWindow.draw(pauseSprite);
        gameWindow.draw(leaderboardSprite);
        gameWindow.display();
        while (gameWindow.pollEvent(gameEvent)) {
            if (gameBoard.leaderBoard) {
                RenderWindow leaderboardWindow(VideoMode(leaderboardWindowWidth, leaderboardWindowHeight), "Leaderboard");
                while (leaderboardWindow.isOpen()) {
                    leaderboardWindow.clear(Color::Blue);
                    Text leaderBoardText = createText("LEADERBOARD", font, 20, Color::White, leaderboardWindowWidth / 2.0f, (leaderboardWindowHeight / 2.0f) - 120);
                    leaderBoardText.setStyle(Text::Bold | Text::Underlined);
                    string combiningHighscoreText = "";
                    for (unsigned int i = 0; i < vectorOfActiveHighscores.size(); i++) {
                        short tempUserTimeInSeconds = vectorOfActiveHighscores.at(i).timeInSec;
                        int tempUserMinInt = tempUserTimeInSeconds / 60;
                        string tempUserMinStr = tempUserMinInt < 10 ? "0" + to_string(tempUserMinInt) : to_string(tempUserMinInt);
                        int tempUserSecInt = tempUserTimeInSeconds % 60;
                        string tempUserSecStr = tempUserSecInt < 10 ? "0" + to_string(tempUserSecInt) : to_string(tempUserSecInt);
                        string tempUserTime = tempUserMinStr + ":" + tempUserSecStr;
                        string tempUserName = vectorOfActiveHighscores.at(i).name;
                        if (newWinnerPosition >= 0 && i == newWinnerPosition)
                            tempUserName += "*";
                        combiningHighscoreText += (i == 0 ? "" : "\n\n") + to_string(i + 1) + "\t" + tempUserTime + "\t" + tempUserName;}
                    Text highscoreText = createText(combiningHighscoreText, font, 18, Color::White, leaderboardWindowWidth / 2.0f, (leaderboardWindowHeight / 2.0f) + 20);
                    highscoreText.setStyle(Text::Bold);
                    Event leaderBoardEvent;
                    while (leaderboardWindow.pollEvent(leaderBoardEvent)) {
                        if (leaderBoardEvent.type == Event::Closed) {
                            gameBoard.leaderBoard = false;
                            if (!gameBoard.is_paused && !gameBoard.loser && !gameBoard.winner) {
                                gameBoard.enableAllTiles();
                                gameClock.start();}
                            leaderboardWindow.close();}}
                    leaderboardWindow.draw(leaderBoardText);
                    leaderboardWindow.draw(highscoreText);
                    leaderboardWindow.display();}}
            if (gameEvent.type == Event::Closed) {
                gameBoard.clear();
                gameWindow.close();
                return 0;}
            if (gameEvent.type == Event::MouseButtonPressed && !gameBoard.leaderBoard) {
                cout << "Mouse clicked at position (" << (gameWindowClickPosition.x / 32) << ", " << (gameWindowClickPosition.y / 32) << ")" << endl;
                if (gameEvent.mouseButton.button == sf::Mouse::Left) {
                    for (unsigned i = 0; i < gameBoard.twoDimensionalVectorOfBoardPointer.size(); i++) {
                        for (unsigned j = 0; j < gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->size(); j++) {
                            if (gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->sprite.getGlobalBounds().contains(gameWindowClick) && gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_enabled) {
                                if (!gameBoard.is_paused && !gameBoard.is_debugMode && !gameBoard.leaderBoard && !gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_mine && !gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_flagged)
                                    gameBoard.reveal(gameWindow, gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j));
                                else if (gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_mine && gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_enabled && !gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_flagged) {
                                    cout << "You Lost!" << endl;
                                    faceTexture.loadFromFile("files/images/face_lose.png");
                                    gameClock.stop();
                                    gameBoard.loser = true;
                                    gameBoard.disableAllTiles();
                                    debugButtonEnabled = false;
                                    pauseButtonEnabled = false;}}}}
                    if (faceSprite.getGlobalBounds().contains(gameWindowClick)) {
                        cout << "RESTARTING" << endl;
                        if (gameBoard.loser)
                            gameBoard.loser = false;
                        if (gameBoard.winner)
                            gameBoard.winner = false;
                        Board newGameBoard;
                        gameBoard.clear();
                        gameBoard = newGameBoard;
                        faceTexture.loadFromFile("files/images/face_happy.png");
                        gameClock.restart();
                        gameClock.start();
                        pauseButtonEnabled = true;
                        debugButtonEnabled = true;}
                    if (debugSprite.getGlobalBounds().contains(gameWindowClick) && debugButtonEnabled) {
                        cout << "debug button pressed" << endl;
                        gameBoard.togDebugMode();
                        if (gameBoard.is_debugMode)
                            gameBoard.disableAllTiles();
                        else
                            gameBoard.enableAllTiles();}
                    if (pauseSprite.getGlobalBounds().contains(gameWindowClick) && pauseButtonEnabled) {
                        if (gameClock.isPaused())
                            gameClock.start();
                        else
                            gameClock.stop();
                        cout << "pause button pressed" << endl;
                        gameBoard.togPauseMode();
                        if (gameBoard.is_paused) {
                            gameClock.stop();
                            gameBoard.disableAllTiles();
                            debugButtonEnabled = false;
                            pauseTexture.loadFromFile("files/images/play.png");
                        } else {
                            gameBoard.enableAllTiles();
                            debugButtonEnabled = true;
                            gameClock.start();
                            pauseTexture.loadFromFile("files/images/pause.png");}}
                    if (leaderboardSprite.getGlobalBounds().contains(gameWindowClick) && !gameBoard.leaderBoard) {
                        cout << "leaderboard button pressed" << endl;
                        gameClock.stop();
                        gameBoard.disableAllTiles();
                        gameBoard.togLeaderBoard();}
                } else if (gameEvent.mouseButton.button == sf::Mouse::Right) {
                    for (unsigned i = 0; i < gameBoard.twoDimensionalVectorOfBoardPointer.size(); i++) {
                        for (unsigned j = 0; j < gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->size(); j++) {
                            if (gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->sprite.getGlobalBounds().contains(gameWindowClick) && !gameBoard.is_paused && !gameBoard.is_debugMode && !gameBoard.loser && !gameBoard.winner) {
                                if (!gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_flagged && !gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_revealed) {
                                    gameBoard.flagsToPlace--;
                                    gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->togFlag();
                                } else if (gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_flagged && !gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->is_revealed && gameBoard.flagsToPlace < gameBoard.mineCount) {
                                    gameBoard.flagsToPlace++;
                                    gameBoard.twoDimensionalVectorOfBoardPointer.at(i)->at(j)->togFlag();}}}}}}}
        if (gameBoard.checkIfWinner()) {
            gameClock.stop();
            gameBoard.flagsToPlace = 0;
            if (!gameBoard.winner) {
                gameBoard.leaderBoard = true;
                newWinnerPosition = -1;
                Player fifthPlacePlayer = vectorOfActiveHighscores.back();
                Player lastPlacePlayer = vectorOfALLHighscoreFileLines.back();
                Player tempPlayer;
                tempPlayer.name = userInput;
                tempPlayer.timeInSec = currentUserSecs + (currentUserMins * 60);
                if (tempPlayer.timeInSec < fifthPlacePlayer.timeInSec) {
                    vectorOfActiveHighscores.pop_back();
                    for (auto iter = vectorOfActiveHighscores.begin(); iter != vectorOfActiveHighscores.end(); iter++) {
                        newWinnerPosition++;
                        if (tempPlayer.timeInSec < iter->timeInSec) {
                            vectorOfActiveHighscores.insert(iter, tempPlayer);
                            break;}}
                    if (vectorOfActiveHighscores.size() < 5) {
                        newWinnerPosition++;
                        vectorOfActiveHighscores.push_back(tempPlayer);}}
                for (auto iter = vectorOfALLHighscoreFileLines.begin(); iter != vectorOfALLHighscoreFileLines.end(); iter++) {
                    if (tempPlayer.timeInSec < iter->timeInSec) {
                        vectorOfALLHighscoreFileLines.insert(iter, tempPlayer);
                        break;}}
                if (tempPlayer.timeInSec >= lastPlacePlayer.timeInSec)
                    vectorOfALLHighscoreFileLines.push_back(tempPlayer);
                highscoreFile.open("files/leaderboard.txt", std::ios::out | std::ios::trunc);
                string tempFileMinsStr;
                string tempFileSecsStr;
                for (auto iter = vectorOfALLHighscoreFileLines.begin(); iter != vectorOfALLHighscoreFileLines.end(); iter++) {
                    short tempFileMins = (iter->timeInSec) / 60;
                    short tempFileSecs = (iter->timeInSec) % 60;
                    tempFileMinsStr = tempFileMins >= 10 ? to_string(tempFileMins) : "0" + to_string(tempFileMins);
                    tempFileSecsStr = tempFileSecs >= 10 ? to_string(tempFileSecs) : "0" + to_string(tempFileSecs);
                    highscoreFile << tempFileMinsStr + ":" + tempFileSecsStr + "," + iter->name << endl;}
                highscoreFile.close();}
            gameBoard.winner = true;
            faceTexture.loadFromFile("files/images/face_win.png");
            gameBoard.disableAllTiles();
            debugButtonEnabled = false;
            pauseButtonEnabled = false;}}
    return 0;
}
