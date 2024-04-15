
#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "main.hpp"
#include "images/FlappyBird.hpp"
#include "DisplayManager.hpp"
#include "Bird.hpp"
#include "images/BlueFlappyBird.hpp"

Bird::Bird() : 
    FlappyBirdSprite(&DisplayManager::tft), 
    BlueFlappyBirdSprite(&DisplayManager::tft),
    yPos(160),
    xPos(40),
    xSize(40),
    ySize(38)
{
    FlappyBirdSprite.createSprite(xSize, ySize);
    FlappyBirdSprite.setSwapBytes(true);
    FlappyBirdSprite.pushImage(0, 0, xSize, ySize, FlappyBird);

    BlueFlappyBirdSprite.createSprite(xSize, ySize);
    BlueFlappyBirdSprite.setSwapBytes(true);
    BlueFlappyBirdSprite.pushImage(0, 0, xSize, ySize, BlueFlappyBird);
}
void Bird::update()
{
    if(yPos >= 270 - ySize )
    {
        gameOver();
    }
    
    if (upbutton) {
        yPos -= 2;
    } else {
        upbutton = false;
        yPos += 1;
    }
    FlappyBirdSprite.pushSprite(xPos, yPos /*, TFT_BLACK*/);
    
}
void Bird::setYPos(int _yPos)
{
    this->yPos = _yPos;
}