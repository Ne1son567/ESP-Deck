#include "games/FlappyBird/Pillar.hpp"
#include "display/DisplayManager.hpp"
#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <vector> 
#include <random>
#include "images/Pillar.hpp"
#include "images/background.hpp"
int step = 2;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> randomGap(52, 65);
std::uniform_int_distribution<> randomHight(80,180);//55, 195

Pillar::Pillar(int _xPos) :
    UpperPillarSprite(&DisplayManager::getDisplay()),
    LowerPillarSprite(&DisplayManager::getDisplay()),
    xPos(_xPos)
{
    xSize = 60;
    ySize = 200;
    yPos = randomHight(gen);
    gap = randomGap(gen);
}
void Pillar::updatePillar()
{
    xPos-= step;
    
    DisplayManager::getDisplay().fillRect(xPos, yPos - ySize - gap, xSize, 200, DisplayManager::tft.color565(155,230,88));
    DisplayManager::getDisplay().drawRect(xPos-1, yPos - ySize - gap-1, xSize+2, 200+2, DisplayManager::tft.color565(0,0,0));
    //DisplayManager::getDisplay().fillRect(xPos + xSize +1, yPos - ySize - gap +1, xSize / 20-1, 200, DisplayManager::tft.color565(113,197,207));

    DisplayManager::renderPartialBitmap(xPos + xSize +1, yPos - ySize - gap +1, xPos + xSize +1, yPos - ySize - gap +1, xSize / 20-1, 200, 480, background);

    DisplayManager::getDisplay().fillRect(xPos, yPos + gap, xSize, 250 - yPos - gap, DisplayManager::tft.color565(155,230,88));
    DisplayManager::getDisplay().drawRect(xPos-1, yPos + gap-1, xSize+2, 250 - yPos - gap+2, DisplayManager::tft.color565(0,0,0));
    //DisplayManager::getDisplay().fillRect(xPos + xSize +1, yPos + gap -1, xSize / 20, 250 - yPos - gap+1, DisplayManager::tft.color565(113,197,207));
    DisplayManager::renderPartialBitmap(xPos + xSize +1, yPos + gap -1, xPos + xSize +1, yPos + gap -1, xSize / 20, 250 - yPos - gap+1, 480, background );
    
    //DisplayManager::tft.drawRect(xPos, 0, 50, 200, TFT_GREEN);
    
}

std::vector<unsigned short> Pillar::flipImage180(const unsigned short* imageData, int width, int height) {
    std::vector<unsigned short> flippedImage(width * height);
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int originalIndex = row * width + col;
            int flippedRow = height - 1 - row;
            int flippedCol = width - 1 - col;
            int flippedIndex = flippedRow * width + flippedCol;
            flippedImage[flippedIndex] = imageData[originalIndex];
        }
    }
    return flippedImage;
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


