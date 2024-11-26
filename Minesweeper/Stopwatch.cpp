#include "Stopwatch.h"

StopWatch::StopWatch() {
    gameTime = sf::Time::Zero;
    gameClock.restart();}
void StopWatch::start() {
    if (paused) {
        gameClock.restart();
        paused = false;}}
void StopWatch::stop() {
    if (!paused) {
        gameTime += gameClock.getElapsedTime();
        paused = true;}}
void StopWatch::restart() {
    gameTime = sf::Time::Zero;
    gameClock.restart();}
sf::Time StopWatch::getElapsedTime() const {
    if (!paused) {
        return gameTime + gameClock.getElapsedTime();
    } else {
        return gameTime;}}
bool StopWatch::isPaused() const {
    return paused;}
