#include "games/FlappyBird/Pillar.hpp"
#include "display/DisplayManager.hpp"
#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <vector> 
#include <random>
#include "images/Pillar.hpp"

int step = 2;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> randomGap(40, 70);
std::uniform_int_distribution<> randomHight(80, 230);

Pillar::Pillar(int _xPos) :
    UpperPillarSprite(&DisplayManager::tft),
    LowerPillarSprite(&DisplayManager::tft),
    xPos(_xPos)
{
    xImageSize = 50;
    yImageSize = 200;
    yPos = randomHight(gen);
    gap = randomGap(gen);
}
void Pillar::updatePillar()
{
    xPos-= step;
    
    DisplayManager::tft.fillRect(xPos, yPos - yImageSize - gap, xImageSize, 200, DisplayManager::tft.color565(113,191,46));
    DisplayManager::tft.fillRect(xPos + xImageSize, yPos - yImageSize - gap, xImageSize / 20, 200, DisplayManager::tft.color565(113,197,207));

    DisplayManager::tft.fillRect(xPos, yPos + gap, xImageSize, 270 - yPos - gap, DisplayManager::tft.color565(113,191,46));
    DisplayManager::tft.fillRect(xPos + xImageSize, yPos + gap, xImageSize / 20, 270 - yPos - gap, DisplayManager::tft.color565(113,197,207));
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