#pragma once
#include <SFML/Graphics.hpp>

class StopWatch {
private:
    sf::Clock gameClock;
    sf::Time gameTime;
    bool paused = false;

public:
    void restart();
    StopWatch();
    sf::Time getElapsedTime() const;
    void start();
    bool isPaused() const;
    void stop();
};
