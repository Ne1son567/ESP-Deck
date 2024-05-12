#ifndef Bird_HPP
#define Bird_HPP

#include <TFT_eSPI.h>
#include "FlappyBird.hpp"
class Bird {
private:
    TFT_eSprite FlappyBirdSprite;
    TFT_eSprite BlueFlappyBirdSprite;
    int yPos;
    int xPos;
    int xSize;
    int ySize;
public:
    Bird();
    void update();
    void gameOverAnimation();
    void jump();
    void setYPos(int _yPos);
    int getYPos();
    int getXPos();
    int getYSize();
    int getXSize();
    
};
#endif
