#ifndef LIGHTSOUT_HPP
#define LIGHTSOUT_HPP

#include "game/Game.hpp"
#include <Arduino.h>
#include <vector>
class LightsOut : public Game
{
    private:
        bool gameOver;
        int tries;
        int cursorX;
        int cursorY;
        int rows;
        int cols;
        int tileSize;
        int gap;
        int edge;
        std::vector<std::vector<bool>> lights;
        void createGame();
        void drawCursor(int xIndex, int yIndex);
    public:
        LightsOut(int difficulty);
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void update(float deltaTime) override;
        void onGameClosed() override;
        
};


#endif