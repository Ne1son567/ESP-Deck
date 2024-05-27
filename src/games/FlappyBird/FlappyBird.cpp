#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <vector>
#include <random>
#include <string>

#include <list>
#include "games/FlappyBird/FlappyBird.hpp"
#include "games/FlappyBird/Bird.hpp"
#include "display/DisplayManager.hpp"
#include "images/Floor.hpp"
#include "images/background.hpp"
#include "games/FlappyBird/Pillar.hpp"

#define up 10
bool upbutton = false;

bool gameover = true;
int score = 0;

int spawnSpeed = 100;
int spawnCounter = 0;


std::list<Pillar> pillars;
Bird myBird;
 
FlappyBird::FlappyBird(int difficulty){
    DisplayManager::getDisplay().setTextSize(1);
    DisplayManager::getDisplay().fillScreen(DisplayManager::tft.color565(113, 197, 207));
    DisplayManager::getDisplay().setTextColor(TFT_WHITE, DisplayManager::tft.color565(220, 215, 147));
    
    DisplayManager::getDisplay().pushImage(0, 250, 480, 70, Floor);
    DisplayManager::getDisplay().pushImage(0, 0, 480, 250, background);
    myBird.update();
    updateScore();
}
void FlappyBird::update() {
  
    if (!gameover) {
        Pillar& pillar = pillars.front();
        myBird.update();
        updatePillars();
        createPillar();
        deletePillar();

        if (pillar.getXPos() + pillar.getXSize() == myBird.getXPos() + myBird.getXSize()){
            
            score++;
            updateScore();
        }
        if(myBird.getYPos() >= 250 - myBird.getYSize() && gameover != true) {
            gameOver();
        }
        if (pillars.size() > 1 && rectanglesTouch(pillar, myBird))
        {
            gameOver();
        }
    } else 
    {  
        if (upbutton && gameover) {
            restartGame();
        }
    }
    
}
void FlappyBird::gameOver()
{
    gameover = true;
    DisplayManager::getDisplay().pushImage(0, 250, 480, 70, Floor);
    DisplayManager::getDisplay().drawString("-GAME OVER-", 170, 290);
    updateScore();
    gameOverAnimation();
    pillars.clear();
}


void FlappyBird::gameOverAnimation()
{
    delay(1500);
    for(int i = 0; i < 125; i ++)
    {
        myBird.gameOverAnimation();
        for (auto& pillar : pillars) 
        {
            
            pillar.gameOverAnimation();
        }
    }
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
    gameover = false;
    spawnCounter = 0;
    score = 0;                               
    DisplayManager::getDisplay().drawString("                         ", 170, 290);
    updateScore();
}

void FlappyBird::keyPressed(int key)
{
    myBird.jump();
    upbutton = true;
}
void FlappyBird::keyReleased(int key)
{
   upbutton = false;
}

bool FlappyBird::rectanglesTouch(Pillar& rect1,  Bird& rect2) {
    
    if (rect2.getXPos() > rect1.getXPos() + rect1.getXSize() ||// rect1 liegt links von rect2
        rect2.getXPos() + rect2.getXSize() < rect1.getXPos() || // rect2 liegt links von rect1
        rect2.getYPos() > rect1.getYPosAbove() && rect2.getYPos() + rect2.getYSize() < rect1.getYPosBelow())   
    {
        return false;
    }
    return true;
}