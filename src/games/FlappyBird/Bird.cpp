
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



int animation = 0;
int currentSpeed;
Bird::Bird() : 
    FlappyBirdSprite(&DisplayManager::getDisplay()), 
    BlueFlappyBirdSprite(&DisplayManager::getDisplay()),
    yPos(120),
    xPos(40),
    xSize(38),
    ySize(28)
{
    gravity = 0.2;
    speed = 1;
}
void Bird::update()
{
    currentSpeed = speed;

    if (speed > - 5)
    {
        speed = speed - gravity;
    }

    yPos = yPos - currentSpeed;
    //DisplayManager::getDisplay().pushImage(xPos, yPos, xSize, ySize+speed * -1, renderFlappyBird(xPos,yPos,xPos,yPos,xSize,ySize,480,background));
    renderFlappyBird();
   

}
void Bird::renderFlappyBird() 
{
    std::vector<unsigned short> partialBackgroundVector(extractPartialBackground(xPos, yPos, xSize, ySize));
    std::vector<unsigned short> birdVector(FlappyBird, FlappyBird + ySize * xSize); //von Zeiger bis zu (Zeiger + 1064)
    std::vector<unsigned short> birdTrailVector;
    std::vector<unsigned short> resultVector; 
    
    for (int i = 0; i < birdVector.size(); i++) {
        if (birdVector[i] == 0x7639) {
            birdVector[i] = partialBackgroundVector[i];
        }
    }
    resultVector.insert(resultVector.end(), birdVector.begin(), birdVector.end());
   
    if (currentSpeed > 0){
        birdTrailVector = extractPartialBackground(xPos, yPos + ySize, xSize, currentSpeed);
        resultVector.insert(resultVector.end(), birdTrailVector.begin(), birdTrailVector.end());
        DisplayManager::getDisplay().pushImage(xPos, yPos, xSize, ySize + currentSpeed, resultVector.data());
    }
    else
    if (currentSpeed < 0){
        birdTrailVector = extractPartialBackground(xPos, yPos - currentSpeed  * - 1, xSize, currentSpeed  * - 1);
        resultVector.insert(resultVector.begin(), birdTrailVector.begin(), birdTrailVector.end());
        DisplayManager::getDisplay().pushImage(xPos, yPos - currentSpeed * -1, xSize, ySize + currentSpeed * -1, resultVector.data());
    }
}
std::vector<unsigned short> Bird::extractPartialBackground(int xPartialBitmap, int yPartialBitmap, int widthPartialBitmap, int heightPartialBitmap)
{
    std::vector<unsigned short> partialBackgroundVector;
    int index = yPartialBitmap * 480 + xPartialBitmap;//Start

    for (int row = 0; row < heightPartialBitmap; row++) {
        
        partialBackgroundVector.insert(partialBackgroundVector.end(), background + index, background + index + widthPartialBitmap);//Zeilenweise 
        index += 480;
    }
    return partialBackgroundVector;
}
void Bird::gameOverAnimation()
{
    animation++;
    if(yPos < 119)
    {
        yPos++;
        if(yPos < 0 - ySize){ //Zu weit oben
            yPos = 120;
        }
        currentSpeed = -1;
        renderFlappyBird();
        
    }else if(yPos > 121)
    {
        yPos--;
        if(yPos < 250 - ySize)//Übermalen vermeiden
        {
            currentSpeed = 1;
            renderFlappyBird();
        }
    }
}
void Bird::jump()
{
    speed = 5;
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