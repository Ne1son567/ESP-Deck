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
int score = 0;
int status = 0;
int spawnSpeed = 100;
static int spawnCounter = 0;
std::list<Pillar> pillars;
const std::chrono::duration<double, std::ratio<1, 55>> target_frame_duration(1); // Ziel-Framedauer von 1/60 Sekunde
Bird myBird;
const int MIN_Y_POS = 250 - myBird.getYSize();

 
FlappyBird::FlappyBird(){
    
    DisplayManager::tft.fillScreen(DisplayManager::tft.color565(113,197,207));
    DisplayManager::tft.setTextColor(TFT_WHITE, DisplayManager::tft.color565(220, 215, 147));

    FloorSprite.createSprite(480, 175);
    FloorSprite.setSwapBytes(true);
    FloorSprite.pushImage(0, 0, 480, 157, Floor);
    FloorSprite.pushSprite(0,250/*, TFT_BLACK*/);
}
void FlappyBird::update() {
    
    auto start_time = std::chrono::steady_clock::now();
    if (pillars.front().getXPos() + pillars.front().getXSize() == myBird.getXPos() + myBird.getXSize()){
        score++;
    }
    
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
        std::string scoreText = "Score: " + std::to_string(score);
        DisplayManager::tft.drawString(scoreText.c_str(),372,290,4);
    } else {
        DisplayManager::tft.drawString("-GAME OVER-", 170, 290, 4);
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
        if(pillar.getXPos() < -81)
        {
            pillars.pop_front();
        }
    }
}
void FlappyBird::restartGame()
{
    pillars.clear();
    DisplayManager::tft.fillScreen(DisplayManager::tft.color565(113,197,207));
    FloorSprite.pushSprite(0,250/*, TFT_BLACK*/);
    myBird.setYPos(120);
    gameover = false;
    spawnCounter = 0;
    score = 0;
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

