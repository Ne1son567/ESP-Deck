#ifndef GAME_HPP
#define GAME_HPP
#include <Arduino.h>
class Game 
{
    public:
        virtual void update() = 0;
        virtual void keyPressed(int key) = 0;
        virtual void keyReleased(int key) = 0;
};

#endif 