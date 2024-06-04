

#include "game/lightsOut/LightsOut.hpp"
#include "display/DisplayManager.hpp"
#include <TFT_eSPI.h>

#include <stdlib.h>
#include <time.h>

LightsOut::LightsOut(int difficulty):
    gameOver(false),
    tries(0),
    cursorX(3),
    cursorY(3)
{   
   TFT_eSPI& display = DisplayManager::getDisplay();
   rows = 5;
   cols = 5;
   tileSize = 58;
   gap = 2;
   edge =  9;
   lights.resize(rows, std::vector<bool>(cols, false));

   display.fillRect(edge, edge, 302, 302, TFT_DARKGREY);
   drawCursor(3, 3);
   createGame();
   delay(1000);
   createGame();
   delay(1000);
   createGame();
   delay(1000);
   createGame();
   delay(1000);
   createGame();
   delay(1000);
}
void LightsOut::createGame()
{
    srand(5);
    TFT_eSPI& display = DisplayManager::getDisplay();
    
    for(int i = 0; i < lights.size(); i++)
    {
        for(int j = 0; j < lights[i].size(); j++)
        {
            lights[i][j] = rand()  % 2 == 0 ? true : false;; //zahlen zu boolean
            if(lights[i][j] == false)
            {
                display.fillRoundRect((i) * (gap + tileSize) + gap + edge, (j) * (gap + tileSize) + gap + edge, tileSize, tileSize, 0, TFT_BLACK);
            }
            else{
                display.fillRoundRect((i) * (gap + tileSize) + gap + edge, (j) * (gap + tileSize) + gap + edge, tileSize, tileSize, 0, TFT_WHITE);
            }
        }
    }
}
void LightsOut::drawCursor(int xIndex, int yIndex)
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRect((xIndex - 1) * (tileSize + gap)  + gap + edge - gap, (yIndex - 1) * (tileSize + gap)  + gap + edge - gap,tileSize + gap*2, tileSize + gap*2, TFT_RED);
    display.drawRect((xIndex - 1) * (tileSize + gap)  + gap + edge - gap + 1, (yIndex - 1) * (tileSize + gap)  + gap + edge - gap + 1, tileSize + gap*2 - 2, tileSize + gap*2 - 2, TFT_RED);
    
}
void LightsOut::update(float deltaTime) 
{

}
void LightsOut::keyPressed(int key) 
{


}
void LightsOut::keyReleased(int key) 
{

}
void LightsOut::onGameClosed() 
{

}