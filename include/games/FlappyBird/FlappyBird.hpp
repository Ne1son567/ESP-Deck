#ifndef FlappyBird_HPP
#define FlappyBird_HPP

#include <vector>
#include "games/Game.hpp"
#include "games/FlappyBird/Pillar.hpp"
#include "games/FlappyBird/Bird.hpp"
class FlappyBird : public Game
{
    private:
    std::uniform_int_distribution<> randomGap;
    std::uniform_int_distribution<> randomHeight;
    public:
        void updatePillars();
        void createPillar();
        void deletePillar();
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void restartGame();
        void gameOver();
        void gameOverAnimation();
        bool checkCollision(Pillar& rect1, Bird& rect2);
        FlappyBird(int difficulty);
        void update() override;
        void updateScore();
};


#endif