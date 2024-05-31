#include "game/flappyBird/FlappyBird.hpp"
#include "display/DisplayManager.hpp"
#include "bitmap/flappyBird/Floor.hpp"
#include "bitmap/flappyBird/background.hpp"
#include "bitmap/flappyBird/gameover.hpp"
#include "bitmap/flappyBird/message.hpp"
#include <TFT_eSPI.h>
#include <list>
#include <random>
#include <string>

bool upbutton = false;
bool gameover = true;
int spawnCounter = 0;

FlappyBird::FlappyBird(int difficulty):
    
    gen(rd()),
    myBird(0.2, 10, 5),
    score(0),
    TapMessageXPos(150),
    TapMessageYPos(180)
{   
    switch (difficulty)
    {
    case 1:
        myBird = Bird(0.15, 5, 4);
        randomGap = std::uniform_int_distribution<>(70, 80);
        randomYPos = std::uniform_int_distribution<>(95, 155);
        speed = 2;
        spawnSpeed = 150;
        break;
    case 2:
        myBird = Bird(0.2, 10, 5);
        randomGap = std::uniform_int_distribution<>(50, 70);
        randomYPos = std::uniform_int_distribution<>(95, 155);
        speed = 2;
        spawnSpeed = 100;
        break;
    case 3:
        
        break;
    
    default:
        break;
    }
    
    
    DisplayManager::getDisplay().setTextSize(1);
    DisplayManager::getDisplay().setTextColor(DisplayManager::tft.color565(113, 197, 207), DisplayManager::tft.color565(220, 215, 147));
    
    DisplayManager::getDisplay().pushImage(0, 250, 480, 70, Floor);
    DisplayManager::getDisplay().pushImage(0, 0, 480, 250, background);
    myBird.update();
    updateScore();
    renderTAPmessage(TapMessageXPos, TapMessageYPos);
}
void FlappyBird::update(float deltaTime) {
    accumulatedTime += deltaTime/1000.0f;

    while (accumulatedTime >= FIXED_TIMESTEP) {
        if (!gameover) {
        
            myBird.update();
            updatePillars();
            createPillar();
            deletePillar();

            Pillar& pillar = pillars.front();
            if (pillar.getXPos() + pillar.getXSize() == myBird.getXPos() + myBird.getXSize()){
                
                score++;
                updateScore();
            }
            if(myBird.getYPos() >= 250 - myBird.getYSize() && gameover != true) {
                gameOver();
            }
            if (pillars.size() != 0 && checkCollision(pillar, myBird))
            {
                gameOver();
            }
        } else 
        {  
            if (upbutton && gameover) { 
                restartGame();
            }
        }
        accumulatedTime -= FIXED_TIMESTEP;
    }
}
void FlappyBird::gameOver()
{
    gameover = true;
    //DisplayManager::getDisplay().drawString("-GAME OVER-", 170, 290);
    DisplayManager::getDisplay().pushImage(0, 250, 480, 70, Floor);
    
    //DisplayManager::getDisplay().pushImage(170, 279, 192, 42, gameoverBitmap);
   
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
    renderTAPmessage(TapMessageXPos, TapMessageYPos);
}
void FlappyBird::updateScore()
{
    DisplayManager::getDisplay().drawString(("Score: " + std::to_string(score)  + "     " ).c_str(),350,290);
}
void FlappyBird::updatePillars() {
    for (auto& pillar : pillars) {
        pillar.updatePillar();
    }
}
void FlappyBird::createPillar() {
   
    spawnCounter++;
    if (spawnCounter % spawnSpeed == 0) {
        
        pillars.push_back(Pillar(randomYPos(gen), randomGap(gen), speed)); 
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
    removeTAPmessage(TapMessageXPos, TapMessageYPos);
    updateScore();
}
void FlappyBird::renderTAPmessage(int x, int y)
{
    int xS = 114;
    int yS = 36;
    
    std::vector<unsigned short> partialBackgroundVector;
    std::vector<unsigned short> messageVector(message, message + yS * xS); //von Zeiger bis zu (Zeiger + 1064)

    int index = y * 480 + x;//Start

    for (int row = 0; row < xS; row++) {
        
        partialBackgroundVector.insert(partialBackgroundVector.end(), background + index, background + index + xS);//Zeilenweise 
        index += 480;
    }
    for (int i = 0; i < messageVector.size(); i++) {
        if (messageVector[i] == 0x7639) {
            messageVector[i] = partialBackgroundVector[i];
        }
    }                 
    //DisplayManager::getDisplay().drawString("                          ", 170, 290);
    DisplayManager::getDisplay().pushImage(x, y, xS, yS, messageVector.data());
}
void FlappyBird::removeTAPmessage(int x, int y)
{
    int xS = 114;
    int yS = 36;
    
    std::vector<unsigned short> partialBackgroundVector;

    int index = y * 480 + x;//Start

    for (int row = 0; row < xS; row++) {
        
        partialBackgroundVector.insert(partialBackgroundVector.end(), background + index, background + index + xS);//Zeilenweise 
        index += 480;
    }
    DisplayManager::getDisplay().pushImage(x, y, xS, yS, partialBackgroundVector.data());
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
bool FlappyBird::checkCollision(Pillar& rect1,  Bird& rect2) {
    
    if (rect2.getXPos() > rect1.getXPos() + rect1.getXSize() ||// rect1 liegt links von rect2
        rect2.getXPos() + rect2.getXSize() < rect1.getXPos() || // rect2 liegt links von rect1
        rect2.getYPos() > rect1.getYPosAbove() && rect2.getYPos() + rect2.getYSize() < rect1.getYPosBelow())   
    {
        return false;
    }
    return true;
}
void FlappyBird::onGameClosed()
{

}