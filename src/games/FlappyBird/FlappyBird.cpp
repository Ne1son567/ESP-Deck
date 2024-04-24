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
#include "images/background.hpp"
#include "games/FlappyBird/Pillar.hpp"
TFT_eSprite backgroundSprite = TFT_eSprite(&DisplayManager::getDisplay());
TFT_eSprite floorSprite = TFT_eSprite(&DisplayManager::getDisplay());

#define up 10
//#define RGB_LED 48
bool upbutton = false;
bool gameover = false;
int score = 0;
int status = 0;
int spawnSpeed = 100;
static int spawnCounter = 0;
bool losgelassen = true;
std::list<Pillar> pillars;
const std::chrono::duration<double, std::ratio<1, 55>> target_frame_duration(1); // Ziel-Framedauer von 1/60 Sekunde
Bird myBird;
const int MIN_Y_POS = 250 - myBird.getYSize();

 
FlappyBird::FlappyBird(){
    DisplayManager::getDisplay().setTextSize(1);
    DisplayManager::getDisplay().setTextColor(TFT_WHITE, DisplayManager::tft.color565(220, 215, 147));

    floorSprite.createSprite(480, 175);
    floorSprite.setSwapBytes(true);
    floorSprite.pushImage(0, 0, 480, 157, Floor);
    floorSprite.pushSprite(0,250/*, TFT_BLACK*/);

    backgroundSprite.createSprite(480, 250);
    backgroundSprite.setSwapBytes(true);
    backgroundSprite.pushImage(0, 0, 480, 250, background);
    backgroundSprite.pushSprite(0,0/*, TFT_BLACK*/);

 
   
    
    updateScore();
}
void FlappyBird::update() {
   
    auto start_time = std::chrono::steady_clock::now();
   
    if (!gameover) {
        Pillar& pillar = pillars.front();
        
        myBird.update();
        createPillar();
        updatePillars();
        deletePillar();
       
        if (pillar.getXPos() + pillar.getXSize() == myBird.getXPos() + myBird.getXSize()){
            
            score++;
            updateScore();
        }
        if(myBird.getYPos() >= MIN_Y_POS) {
            gameOver();
        }
        if (pillars.size() > 1 && rectanglesIntersect(pillar, myBird) )
        {
            gameOver();
        }

    } else {
        
        if (upbutton && gameover) {
            restartGame();
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto update_duration = end_time - start_time;

    if (update_duration < target_frame_duration) {
        std::this_thread::sleep_for(target_frame_duration - update_duration);
    }
    
}
void FlappyBird::gameOver()
{
    gameover = true;
    pillars.clear();
    floorSprite.pushSprite(0,250/*, TFT_BLACK*/);
    DisplayManager::getDisplay().drawString("-GAME OVER-", 170, 290);
    updateScore();
}
void FlappyBird::updateScore()
{
    DisplayManager::getDisplay().drawString(("Score: " + std::to_string(score)).c_str(),372,290);
}
void FlappyBird::updatePillars() {
    for (auto& pillar : pillars) {
        pillar.updatePillar();
    }
}
void FlappyBird::createPillar() {
   
    spawnCounter++;
    if (spawnCounter % spawnSpeed == 0) {
        pillars.push_back(Pillar(480)); 
        
        //spawnSpeed --;
    }
}
void FlappyBird::deletePillar()
{
    for (auto& pillar : pillars) {
        if(pillar.getXPos() < -60)
        {
            pillars.pop_front();
        }
    }
}
void FlappyBird::restartGame()
{
    DisplayManager::getDisplay().fillScreen(DisplayManager::getDisplay().color565(113,197,207));
    floorSprite.pushSprite(0,250/*, TFT_BLACK*/);
    myBird.setYPos(120);
    gameover = false;
    spawnCounter = 0;
    score = 0;
}

void FlappyBird::input(int key)
{
    if (key == 1 && losgelassen == true) {
        upbutton = true;
        myBird.jump();
        losgelassen = false;
    }
    else{
        upbutton = false;
        if (key != 1 ) 
        {
            losgelassen = true;
        }
        
    }
}

bool FlappyBird::rectanglesIntersect(Pillar& rect1,  Bird& rect2) {
    
    if (rect2.getXPos() > rect1.getXPos() + rect1.getXSize() ||// rect1 liegt links von rect2
        rect2.getXPos() + rect2.getXSize() < rect1.getXPos() || // rect2 liegt links von rect1
        rect2.getYPos() > rect1.getYPosAbove() && rect2.getYPos() + rect2.getYSize() < rect1.getYPosBelow())   
    {
        return false;
    }
    return true;
}