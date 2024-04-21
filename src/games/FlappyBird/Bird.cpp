
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <cmath>
#include "games/FlappyBird/FlappyBird.hpp"
#include "images/Flugzeug.hpp"
#include "images/FlappyBird.hpp"
#include "display/DisplayManager.hpp"
#include "games/FlappyBird/Bird.hpp"
#include "images/BlueFlappyBird.hpp"

float speed = -2;

Bird::Bird() : 
    FlappyBirdSprite(&DisplayManager::tft), 
    BlueFlappyBirdSprite(&DisplayManager::tft),
    yPos(120),
    xPos(40),
    xSize(38),
    ySize(28)
{
    FlappyBirdSprite.createSprite(xSize, ySize);
    FlappyBirdSprite.setSwapBytes(true);
    FlappyBirdSprite.pushImage(0, 0, xSize, ySize, FlappyBird);
}
void Bird::update()
{
    
    yPos = yPos - speed;
    FlappyBirdSprite.pushSprite(xPos, yPos /*, TFT_BLACK*/);
    if (speed != -8)
    {
        speed = speed - 0.2;
    }
    if(speed > 0)
    {
        DisplayManager::tft.fillRect(xPos, yPos + ySize, xSize, 8, DisplayManager::tft.color565(113,197,207));
    }
    if(speed < 0)
    {
        DisplayManager::tft.fillRect(xPos , yPos - 8, xSize, 8, DisplayManager::tft.color565(113,197,207));
    }
    
}
void Bird::jump()
{
    speed = 4;
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