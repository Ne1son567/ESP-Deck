#ifndef Bird_HPP
#define Bird_HPP

#include <TFT_eSPI.h>

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
    void setYPos(int _yPos);

};
#endif
