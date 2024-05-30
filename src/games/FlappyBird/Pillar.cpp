#include "games/FlappyBird/Pillar.hpp"
#include "display/DisplayManager.hpp"
#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <vector> 
#include <random>
#include "images/Pillar.hpp"
#include "images/background.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> randomGap(50, 70);
std::uniform_int_distribution<> randomHight(95,155);//55, 195

Pillar::Pillar(int _xPos) :
    UpperPillarSprite(&DisplayManager::getDisplay()),
    LowerPillarSprite(&DisplayManager::getDisplay()),
    xPos(_xPos)
{
    xSize = 58;
    ySize = 200;
    step = 2;
    openingXSize = xSize + 6;
    openingYSize = 15;
    yPos = randomHight(gen);
    gap = randomGap(gen);
}
void Pillar::updatePillar()
{
    xPos-= step;
    DisplayManager::getDisplay().fillRect(xPos + 1, yPos - ySize - gap - openingYSize + 1, xSize -2, ySize-1, DisplayManager::tft.color565(7, 219, 64));//Oben
    DisplayManager::getDisplay().drawRect(xPos, yPos - ySize - gap - openingYSize, xSize, ySize+1, DisplayManager::tft.color565(0,0,0));
    DisplayManager::renderPartialBitmap(xPos + xSize, yPos - ySize - gap - openingYSize, xPos + xSize, yPos - ySize - gap - openingYSize, step, ySize, 480, background);

    DisplayManager::tft.fillRect(xPos - ((openingXSize-xSize)/2) + 1, yPos - gap - openingYSize + 1, openingXSize -2, openingYSize -2, DisplayManager::tft.color565(7, 219, 64));
    DisplayManager::tft.drawRect(xPos - ((openingXSize-xSize)/2), yPos - gap - openingYSize , openingXSize, openingYSize, DisplayManager::tft.color565(0, 0, 0));
    DisplayManager::renderPartialBitmap(xPos - ((openingXSize - xSize) / 2) + openingXSize, yPos - gap - openingYSize , xPos - ((openingXSize - xSize) / 2) + openingXSize ,  yPos - gap - openingYSize, step, openingYSize, 480, background);
   
    DisplayManager::getDisplay().fillRect(xPos + 1, yPos + gap + openingYSize, xSize-2, 250 - yPos - gap - openingYSize, DisplayManager::tft.color565(7, 219, 64));//Unten 
    DisplayManager::getDisplay().drawRect(xPos, yPos + gap + openingYSize-1, xSize, 250 - yPos - gap - openingYSize+2, DisplayManager::tft.color565(0, 0, 0));
    DisplayManager::renderPartialBitmap(xPos + xSize, yPos + gap + openingYSize-1, xPos + xSize, yPos + gap + openingYSize-1, step, 250 - yPos - gap - openingYSize +1, 480, background);

    DisplayManager::tft.fillRect(xPos - ((openingXSize-xSize)/2)+1, yPos + gap + 1, openingXSize -2, openingYSize -2, DisplayManager::tft.color565(7, 219, 64));
    DisplayManager::tft.drawRect(xPos - ((openingXSize-xSize)/2), yPos + gap, openingXSize, openingYSize, DisplayManager::tft.color565(0,0,0));
    DisplayManager::renderPartialBitmap(xPos - ((openingXSize - xSize) / 2) + openingXSize, yPos + gap ,xPos - ((openingXSize - xSize) / 2) + openingXSize, yPos + gap , step, openingYSize, 480, background);
   
}
void Pillar::gameOverAnimation()
{
    delay(5);
    gap += 1;
    DisplayManager::tft.fillRect(xPos - ((openingXSize-xSize)/2) + 1, yPos - gap - openingYSize + 1, openingXSize -2, openingYSize -2, DisplayManager::tft.color565(7, 219, 64));
    DisplayManager::tft.drawRect(xPos - ((openingXSize-xSize)/2), yPos - gap - openingYSize , openingXSize, openingYSize, DisplayManager::tft.color565(0,0,0));
    DisplayManager::renderPartialBitmap(xPos - ((openingXSize-xSize)/2), yPos - gap, xPos - ((openingXSize-xSize)/2) , yPos - gap, openingXSize, 2 , 480, background);

    if(yPos + gap + openingYSize <= 251)
    {
        DisplayManager::tft.fillRect(xPos - ((openingXSize-xSize)/2)+1, yPos + gap + 1, openingXSize -2, openingYSize - 2, DisplayManager::tft.color565(7, 219, 64));
        DisplayManager::tft.drawRect(xPos - ((openingXSize-xSize)/2), yPos + gap, openingXSize, openingYSize, DisplayManager::tft.color565(0,0,0));
        DisplayManager::renderPartialBitmap(xPos - ((openingXSize-xSize)/2), yPos + gap - 2, xPos - ((openingXSize-xSize)/2) , yPos + gap -2, openingXSize, 2 , 480, background);
    }
    else if(yPos + gap <= 251)
    {
        DisplayManager::renderPartialBitmap(xPos - ((openingXSize-xSize)/2), yPos + gap - 2, xPos - ((openingXSize-xSize)/2) , yPos + gap -2, openingXSize, 2 , 480, background);
        DisplayManager::tft.drawFastHLine(xPos - ((openingXSize-xSize)/2), yPos + gap -1, openingXSize, TFT_BLACK);
    }
}

int Pillar::getXPos(){
    return xPos;
}
int Pillar::getYPosAbove(){
    return yPos - gap;
}
int Pillar::getYPosBelow(){
    return yPos + gap;
}
int Pillar::getXSize(){
    return xSize;
}
int Pillar::getYSize(){
    return ySize;
}


