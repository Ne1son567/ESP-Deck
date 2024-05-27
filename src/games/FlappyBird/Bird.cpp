
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
int animation = 0;

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
    FlappyBirdSprite.pushSprite(xPos, yPos , DisplayManager::tft.color565(113,197,207));
}
void Bird::update()
{
    if (speed > - 5)
    {
        speed = speed - 0.20;
    }
    yPos = round(yPos - speed);
    FlappyBirdSprite.pushImage(0, 0, xSize, ySize, renderFlappyBird(xPos,yPos,xPos,yPos,xSize,ySize,480,background));
    //DisplayManager::getDisplay().pushImage(xPos,yPos,xSize,ySize,);
        FlappyBirdSprite.pushSprite(xPos, yPos);

    
}
const uint16_t*  Bird::renderFlappyBird(int xPartialBitmap, int yPartialBitmap, int xOnBitmap, int yOnBitmap, int widthPartialBitmap, int heightPartialBitmap, int widthBitmap, const unsigned short* bitmap) 
{
    std::vector<unsigned short> paritalVectorBitmap;
    std::vector<unsigned short> resultBitmap(FlappyBird, FlappyBird + 1064); //Zeiger array bis zu Zeiger + 1064 => alle adressen von FlappyBird
    int index = yOnBitmap * widthBitmap + xOnBitmap;

    for (int row = 0; row < heightPartialBitmap; row++) {
        for (int col = 0; col < widthPartialBitmap; col++) {
            paritalVectorBitmap.push_back(bitmap[index]);
            index++;
        }
        index += widthBitmap - widthPartialBitmap;
    }

    for (int row = 0; row < heightPartialBitmap; row++) {
        for (int col = 0; col < widthPartialBitmap; col++) {
            if (resultBitmap[row * widthPartialBitmap + col] == 0x7639) {
                resultBitmap[row * widthPartialBitmap + col] = paritalVectorBitmap[row * widthPartialBitmap + col];
            }
        }
    }
    const unsigned short* values = resultBitmap.data();
    return reinterpret_cast<const uint16_t*>(values);
}
void Bird::gameOverAnimation()
{
    animation++;
    if(yPos < 119)
    {
        if(yPos < 0 - ySize){
            yPos = 120;
        }
        DisplayManager::getDisplay().pushImage(xPos,yPos,xSize,ySize,renderFlappyBird(xPos,yPos,xPos,yPos,xSize,ySize,480,background));
        DisplayManager::renderPartialBitmap(xPos, yPos - 5, xPos, yPos - 5, xSize, 5, 480, background);
        yPos++;
    }else if(yPos > 121)
    {
        if(yPos < 250 - ySize - 4)//Übermalen vermeiden
        {
            DisplayManager::getDisplay().pushImage(xPos,yPos,xSize,ySize,renderFlappyBird(xPos,yPos,xPos,yPos,xSize,ySize,480,background));
            DisplayManager::renderPartialBitmap(xPos, yPos + ySize , xPos, yPos + ySize , xSize, 5, 480, background);
        }
        yPos--;
    }
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