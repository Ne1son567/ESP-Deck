#ifndef FlappyBird_HPP
#define FlappyBird_HPP

#include <vector>
#include "games/Game.hpp"
#include "games/FlappyBird/Pillar.hpp"
#include "games/FlappyBird/Bird.hpp"
class FlappyBird : public Game
{
    
    public:
        void updatePillars();
        void createPillar();
        void deletePillar();
        void displayInitialize();
        void inputLoop(void * parameter);
        void restartGame();
        void gameOver();
        bool rectanglesIntersect(Pillar& rect1, Bird& rect2);
        std::vector<unsigned short> flipImage180(const unsigned short* imageData, int width, int height);
        FlappyBird();
        void update() override;
        void input(int key) override;
};


#endif