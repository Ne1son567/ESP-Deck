#ifndef FlappyBird_HPP
#define FlappyBird_HPP

#include <vector>
#include "games/Game.hpp"

class FlappyBird : public Game
{
    
    public:
        
        void createPillar();
        void deletePillar();
        void displayInitialize();
        void inputLoop(void * parameter);
        void restard();
        void gameOver();
        std::vector<unsigned short> flipImage180(const unsigned short* imageData, int width, int height);
        FlappyBird();
        void update() override;
        void input(int key) override;
};


#endif