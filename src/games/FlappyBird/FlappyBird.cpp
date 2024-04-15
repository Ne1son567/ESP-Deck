#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <vector> // Inkludieren der Header-Datei für Vektoren
#include <random>
#include "games/FlappyBird/FlappyBird.hpp"
#include "games/FlappyBird/Bird.hpp"
#include "display/DisplayManager.hpp"
#include "DynamicArray.hpp"
#include "images/Floor.hpp"
#include "games/FlappyBird/Pillar.hpp"
TFT_eSprite FloorSprite = TFT_eSprite(&DisplayManager::tft);

#define up 10
//#define RGB_LED 48
bool upbutton = false;
bool gameover = false;
int spawn = 0;
int spawnSpeed = 200;
DynamicArray pillars;
Bird myBird;

    
unsigned long previousMillis = 0;
const unsigned long interval = 15; 
FlappyBird::FlappyBird(){
    
    DisplayManager::tft.fillScreen(DisplayManager::tft.color565(113,197,207));
    
    FloorSprite.createSprite(480, 50);
    FloorSprite.setSwapBytes(true);
    FloorSprite.pushImage(0, 0, 480, 156, Floor);
    FloorSprite.pushSprite(0,270/*, TFT_BLACK*/);
    
   
}
void FlappyBird::update() {

    if(upbutton == true)
    {
        yPos -= 2;
    }
    else{
        
        yPos += 1;
    }
    if(myBird.getYPos() >= 270 - myBird.getYSize() )
    {
        gameOver();
    }
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) 
    {
        previousMillis = currentMillis; 

        if (gameover == false) 
        {
            myBird.update();
            
            createPillar();

            Pillar** array = pillars.getArray();
            for (int i = 0; i < pillars.getSize(); i++) {
                array[i]->updatePillar(); 
            }
            
            deletePillar();
            
        } else {
            DisplayManager::tft.drawString("-GAME OVER-", 170, 160, 4);
            if(upbutton == true && gameover == true){
                restard();
            }
            
        }
    }
}
void FlappyBird::createPillar() {
    static int counter = 0;
    counter++;
    if (counter % spawnSpeed == 0) {
        pillars.add(Pillar(480)); 
        spawnSpeed --;
    }
}
void FlappyBird::deletePillar()
{
    Pillar** array = pillars.getArray();
    for (int i = 0; i < pillars.getSize(); i++) 
    {
        if(array[i]->getXPos() < -50)
        {
            pillars.remove(i);
        }
    }
}
void FlappyBird::restard()
{
    delete[] pillars.getArray();
    DisplayManager::tft.fillScreen(DisplayManager::tft.color565(113,197,207));
    FloorSprite.pushSprite(0,270/*, TFT_BLACK*/);
    myBird.setYPos(160);
    gameover = false;
    
}
void FlappyBird::gameOver()
{
    gameover = true;
}
void FlappyBird::input(int key) 
{
    
    if (key == 0) {
        myBird.setYPos(myBird.getYPos() +1);
    }
    else{
        myBird.setYPos(myBird.getYPos() -1);
    }

    delay(50);
    
}
bool getUpButton()
{
    return upbutton;
}
