
#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "main.hpp"
#include "images/FlappyBird.hpp"
#include "DisplayManager.hpp"
#include "Bird.hpp"

Bird::Bird() : 
    FlappyBirdSprite(&DisplayManager::tft), 
    yPos (160),
    xPos (40),
    xSize(40),
    ySize (37)
{
    FlappyBirdSprite.createSprite(xSize, ySize);
    FlappyBirdSprite.setSwapBytes(true);
    FlappyBirdSprite.pushImage(0, 0, xSize, ySize, FlappyBird);
}
void Bird::update()
{
    if(yPos >= 270 - ySize )
    {
        gameOver();
    }
    FlappyBirdSprite.pushSprite(xPos, yPos /*, TFT_BLACK*/);
    if (upbutton) {
        yPos -= 4;
    } else {
        upbutton = false;
        yPos += 3;
    }
}
void Bird::setYPos(int _yPos)
{
    this->yPos = _yPos;
}