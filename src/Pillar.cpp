#include "Pillar.hpp"
#include "DisplayManager.hpp"
#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <vector> // Inkludieren der Header-Datei für Vektoren
#include "images/Pillar.h"
int step = 2;
Pillar::Pillar(int _xPos, int _yPos, int _gap) :
    UpperPillarSprite(&DisplayManager::tft),
    LowerPillarSprite(&DisplayManager::tft),
    xPos(_xPos),
    yPos(_yPos),
    gap(_gap)
{
    xImageSize = 50;
    yImageSize = 200;
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