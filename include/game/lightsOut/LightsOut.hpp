#ifndef LIGHTSOUT_HPP
#define LIGHTSOUT_HPP

#include "game/Game.hpp"
#include <Arduino.h>
#include <vector>
class LightsOut : public Game
{
    private:
        bool gameOver;
        int moves;
        int cursorX;
        int cursorY;
        int rows;
        int cols;
        int tileSize;
        int gap;
        int edge;
        int minCount;
        int maxCount;
        String difficultyText;
    
        std::vector<std::vector<bool>> lights;
        void createGame();
        void moveCursor(int xIndex, int yIndex);
        void invertOne(int xIndex, int yIndex);
        void inevertAllPossibleOnes(int xIndex, int yIndex);
        void checkWin();
        void showSolved();
        void hideSolved();
        void updateMoves();
    public:
        LightsOut(int difficulty);
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void update(float deltaTime) override;
        void onGameClosed() override;
        
};


#endif