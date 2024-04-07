#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <vector> // Inkludieren der Header-Datei für Vektoren
#include <random>
#include "main.hpp"
#include "Pillar.hpp"
#include "DisplayManager.hpp"
#include "DynamicArray.hpp"
#include "images/Floor.h"
#include "Bird.hpp"
TaskHandle_t core0TaskHandle;
TFT_eSprite FloorSprite = TFT_eSprite(&DisplayManager::tft);

#define up 10
//#define RGB_LED 48
bool upbutton = false;
bool gameover = false;
int spawn = 0;
int spawnSpeed = 200;
DynamicArray pillars;
Bird myBird;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> randomGap(30, 60);
std::uniform_int_distribution<> randomHight(80, 240);
    
unsigned long previousMillis = 0;
const unsigned long interval = 15; 
void setup()
{
    DisplayManager::initialize();
    DisplayManager::tft.fillScreen(DisplayManager::tft.color565(113,197,207));
    pinMode(up, INPUT_PULLUP);
    
    FloorSprite.createSprite(480, 50);
    FloorSprite.setSwapBytes(true);
    FloorSprite.pushImage(0, 0, 480, 156, Floor);
    FloorSprite.pushSprite(0,270/*, TFT_BLACK*/);
    
    xTaskCreatePinnedToCore(
        inputLoop,
        "Input",
        10000,
        NULL,
        1,
        &core0TaskHandle,
        0
    );
}
void loop() {
    
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
void createPillar() {
    static int counter = 0;
    counter++;
    if (counter % spawnSpeed == 0) {
        pillars.add(Pillar(480, randomHight(gen), randomGap(gen))); 
        spawnSpeed --;
    }
}
void deletePillar()
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
void restard()
{
    delete[] pillars.getArray();
    DisplayManager::tft.fillScreen(DisplayManager::tft.color565(113,197,207));
    FloorSprite.pushSprite(0,270/*, TFT_BLACK*/);
    myBird.setYPos(160);
    gameover = false;
    
}
void gameOver()
{
    gameover = true;
}
void inputLoop(void * parameter)
{
    for (;;) {
        
        if (digitalRead(up) == LOW) {
            upbutton = true;
        }
        else{
            upbutton = false;
        }
    
        delay(50);
    }
}
bool getUpButton()
{
    return upbutton;
}
