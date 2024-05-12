
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <cmath>
#include "games/FlappyBird/FlappyBird.hpp"
#include "images/Flugzeug.hpp"
#include "images/FlappyBird.hpp"
#include "display/DisplayManager.hpp"
#include "games/FlappyBird/Bird.hpp"
#include "images/BlueFlappyBird.hpp"
#include "images/background.hpp"

float speed = -2;

Bird::Bird() : 
    FlappyBirdSprite(&DisplayManager::getDisplay()), 
    BlueFlappyBirdSprite(&DisplayManager::getDisplay()),
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
    if (speed > - 4)
    {
        speed = speed - 0.20;
    }
    yPos = round(yPos - speed);
    FlappyBirdSprite.pushSprite(xPos, yPos /*,DisplayManager::tft.color565(113,197,207)*/);

    if(speed < 0)
    {
        //DisplayManager::tft.fillRect(xPos , yPos - 8, xSize, 8, TFT_BLACK);
        DisplayManager::renderPartialBitmap(xPos, yPos - 5, xPos, yPos - 5, xSize, 5, 480, background);
        
        //DisplayManager::renderPartialBitmap(xPos, yPos - speed * - 1, xPos, yPos - speed * -1, xSize, speed * -1+1, 480, background)
    }
    else
    if(speed > 0)
    {
        //DisplayManager::tft.fillRect(xPos, yPos + ySize, xSize, 8, TFT_BLACK);
        DisplayManager::renderPartialBitmap(xPos, yPos + ySize, xPos, yPos + ySize, xSize, 5, 480, background);

        //DisplayManager::renderPartialBitmap(xPos, yPos + ySize, xPos, yPos + ySize, xSize, round(speed) +1 , 480, background);

    }
}
void Bird::gameOverAnimation()
{
    DisplayManager::renderPartialBitmap(xPos, yPos , xPos, yPos , xSize, ySize, 480, background);
}
void Bird::jump()
{
    speed = 5;
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