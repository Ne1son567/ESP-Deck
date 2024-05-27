#include "Main.hpp"
#include <Arduino.h>
#include <memory>
#include <chrono>
#include <thread>
#include "games/Game.hpp"
#include "games/FlappyBird/FlappyBird.hpp"
#include "display/DisplayManager.hpp"
#include "TFT_eSPI.h"
#include "images/background.hpp"

#define RIGHT_PIN 9
#define UP_PIN 10
#define LEFT_PIN 11
#define DOWN_PIN 12
#define ACTION_PIN 13
#define MENU_PIN 46
int keyPins[] = {RIGHT_PIN, UP_PIN, LEFT_PIN, DOWN_PIN, ACTION_PIN};
TaskHandle_t core0TaskHandle;
const std::chrono::duration<double, std::ratio<1, 55>> target_frame_duration(1); // Ziel-Framedauer von 1/60 Sekunde

std::unique_ptr<Game> currentGame;
bool menuButtonPressed = false;
bool upButtonPressed = false;

void setup() 
{
    Serial.begin(9600);

        pinMode(RIGHT_PIN, INPUT_PULLUP);
    pinMode(UP_PIN, INPUT_PULLUP);
    pinMode(LEFT_PIN, INPUT_PULLUP);
    pinMode(DOWN_PIN, INPUT_PULLUP);
    pinMode(ACTION_PIN, INPUT_PULLUP);
    pinMode(MENU_PIN, INPUT_PULLUP);

    xTaskCreatePinnedToCore(
        inputLoop,
        "Input",
        10000,
        NULL,
        3,
        &core0TaskHandle,
        1
    );

    DisplayManager::initialize();
    currentGame = std::unique_ptr<FlappyBird>(new FlappyBird(2));
}
void loop()
{ //ChatGPT -_-
    auto startTime = std::chrono::steady_clock::now();

    currentGame->update();

    auto endTime = std::chrono::steady_clock::now();
    auto update_duration = endTime - startTime;

    if (update_duration < target_frame_duration) {
        std::this_thread::sleep_for(target_frame_duration - update_duration);
    }
}

void inputLoop(void * parameter)
{
    bool menuButtonSpamProt = true;
    bool keyStates[5] = {false};

    for (;;) {
        if (!menuButtonPressed) {
            if (digitalRead(MENU_PIN) == LOW && menuButtonSpamProt) {
                menuButtonPressed = true;
                menuButtonSpamProt = false;
            } else if (digitalRead(MENU_PIN) == HIGH) {
                menuButtonSpamProt = true;
            }
            
            for (int key = 0; key < 5; ++key) {
                int pin = keyPins[key];
                bool &keyState = keyStates[key];
                
                if (digitalRead(pin) == LOW && !keyState) {
                    currentGame->keyPressed(key);
                    keyState = true;
                } else if (digitalRead(pin) == HIGH && keyState) {
                    currentGame->keyReleased(key);
                    keyState = false;
                }
            }
        }
        delay(50);
    }
}