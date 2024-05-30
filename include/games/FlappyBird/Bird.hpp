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
    float gravity;
    float speed;
public:

    Bird();
    void update();
    void renderFlappyBird();
    std::vector<unsigned short> extractPartialBackground(int xPartialBitmap, int yPartialBitmap, int widthPartialBitmap, int heightPartialBitmap);
    void gameOverAnimation();
    void jump();
    int getYPos();
    int getXPos();
    int getYSize();
    int getXSize();
    
};
#endif
