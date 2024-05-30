#ifndef FlappyBird_HPP
#define FlappyBird_HPP

#include "game/Game.hpp"
#include "game/FlappyBird/Pillar.hpp"
#include "game/FlappyBird/Bird.hpp"
#include <Arduino.h>
#include <random>
#include <list>

class FlappyBird : public Game
{
    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> randomGap;
        std::uniform_int_distribution<> randomYPos;
        std::list<Pillar> pillars;
        Bird myBird;
        int speed;
        int score;
        int spawnSpeed;
        int TapMessageYPos;
        int TapMessageXPos;
        void updatePillars();
        void createPillar();
        void deletePillar();
        void restartGame();
        void gameOver();
        void gameOverAnimation();
        void renderTAPmessage(int x, int y);
        void removeTAPmessage(int x, int y);
        bool checkCollision(Pillar& rect1, Bird& rect2);
        void updateScore();

    public:
        FlappyBird(int difficulty);
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void update() override;
        
};


#endif