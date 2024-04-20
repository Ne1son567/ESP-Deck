
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include "games/FlappyBird/FlappyBird.hpp"
#include "images/FlappyBird.hpp"
#include "display/DisplayManager.hpp"
#include "games/FlappyBird/Bird.hpp"
#include "images/BlueFlappyBird.hpp"

Bird::Bird() : 
    FlappyBirdSprite(&DisplayManager::tft), 
    BlueFlappyBirdSprite(&DisplayManager::tft),
    yPos(120),
    xPos(40),
    xSize(40),
    ySize(38)
{
    FlappyBirdSprite.createSprite(xSize, ySize);
    FlappyBirdSprite.setSwapBytes(true);
    FlappyBirdSprite.pushImage(0, 0, xSize, ySize, FlappyBird);
}
void Bird::update()
{
    FlappyBirdSprite.pushSprite(xPos, yPos /*, TFT_BLACK*/);
}
void Bird::jump()
{
    
}
void Bird::setYPos(int _yPos)
{
    yPos = _yPos;
}
int Bird::getYPos()
{
    return yPos;
}
int Bird::getXPos()
{
    return xPos;
}
int Bird::getYSize()
{
    return ySize;
}
int Bird::getXSize()
{
    return xSize;
}