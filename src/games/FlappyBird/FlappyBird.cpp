#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <list>
#include <thread>
#include "games/FlappyBird/FlappyBird.hpp"
#include "games/FlappyBird/Bird.hpp"
#include "display/DisplayManager.hpp"
#include "images/Floor.hpp"
#include "games/FlappyBird/Pillar.hpp"
TFT_eSprite FloorSprite = TFT_eSprite(&DisplayManager::tft);

#define up 10
//#define RGB_LED 48
bool upbutton = false;
bool gameover = false;
int status = 0;
int spawnSpeed = 100;
static int spawnCunter = 0;
std::list<Pillar> pillars;
Bird myBird;
const int MIN_Y_POS = 270 - myBird.getYSize();

 
FlappyBird::FlappyBird(){
    
    DisplayManager::tft.fillScreen(DisplayManager::tft.color565(113,197,207));
    
    FloorSprite.createSprite(480, 50);
    FloorSprite.setSwapBytes(true);
    FloorSprite.pushImage(0, 0, 480, 156, Floor);
    FloorSprite.pushSprite(0,270/*, TFT_BLACK*/);
}
void FlappyBird::update() {
    
    static unsigned long lastUpdateTime = 0; 
    unsigned long currentTime = millis(); 
    unsigned long updateInterval = 20; 

    if (currentTime - lastUpdateTime >= updateInterval) {
        lastUpdateTime = currentTime; 

        if(myBird.getYPos() >= MIN_Y_POS) {
            gameover = true;
        }
        if(upbutton == true) {
            myBird.setYPos(myBird.getYPos() - 3);
        } else {
            myBird.setYPos(myBird.getYPos() + 2);
        }
        if (!gameover) {
            myBird.update();
            createPillar();
            updatePillars();
            deletePillar();
        } else {
            DisplayManager::tft.drawString("-GAME OVER-", 170, 160, 4);
            if (upbutton && gameover) {
                restartGame();
            }
        }
    }
    
}
void FlappyBird::updatePillars() {
    for (auto& pillar : pillars) {
        pillar.updatePillar();
    }
}
void FlappyBird::createPillar() {
    
    spawnCunter++;
    if (spawnCunter % spawnSpeed == 0) {
        pillars.push_back(Pillar(480)); 
        
        //spawnSpeed --;
    }
}
void FlappyBird::deletePillar()
{
    for (auto& pillar : pillars) {
        if(pillar.getXPos() < -50)
        {
            pillars.pop_front();
        }
    }
}
void FlappyBird::restartGame()
{
    pillars.clear();
    DisplayManager::tft.fillScreen(DisplayManager::tft.color565(113,197,207));
    FloorSprite.pushSprite(0,270/*, TFT_BLACK*/);
    myBird.setYPos(160);
    gameover = false;
    spawnCunter = 0;
}

void FlappyBird::input(int key)
{
    if (key == 1) {
        upbutton = true;
    }
    else{
        upbutton = false;
    }
}

