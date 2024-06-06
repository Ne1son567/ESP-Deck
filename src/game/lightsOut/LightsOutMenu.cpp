
#include "bitmap/TrophyGoldenBitmap.hpp"
#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/lightsOut/LightsOutMenu.hpp"
#include "font/Fonts.hpp"
#include "display/DisplayManager.hpp"
#include <game/menu/Menu.hpp>
#include "eeprom/EepromManager.hpp"

LightsOutMenu::FlappyBirdMenu() 
{

}

void LightsOutMenu::renderMenu()
{
    menuIndex = 0;
    menuButtonAmount = 3;

    backgroundSprite.pushImage(-60, -1, 480, 250, skyBackgroundBitmap);
    backgroundSprite.pushImage(-60, 249, 480, 70, floorBitmap);
    backgroundSprite.pushSprite(60, 1);

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setFreeFont(FF24);
    display.setTextColor(TFT_DARKGREY);
    //display.drawString("FlappyBird", 125, 40);
    DisplayManager::resetFont();
    display.fillRoundRect(310, 135, 150, 40, 10, 0xFEE0);
    display.fillRoundRect(150, 130, 180, 50, 10, TFT_WHITE);
    display.pushImage(330, 138, 35, 35, trophyGoldenBitmap);
    display.drawString("Easy", 178, 139);

    display.fillRoundRect(310, 195, 150, 40, 10, 0xFEE0);
    display.fillRoundRect(150, 190, 180, 50, 10, TFT_WHITE);
    display.pushImage(330, 198, 35, 35, trophyGoldenBitmap);
    display.drawString("Normal", 182, 199);

    display.fillRoundRect(310, 255, 150, 40, 10, 0xFEE0);
    display.fillRoundRect(150, 250, 180, 50, 10, TFT_WHITE);
    display.pushImage(330, 258, 35, 35, trophyGoldenBitmap);
    display.drawString("Hard", 185, 259);

    int highscores[] = {
        EepromManager::readInt16(EepromManager::EEPROM_FlappyBird_EASY_HIGHSCORE_ADDR_INT16),
        EepromManager::readInt16(EepromManager::EEPROM_FlappyBird_NORMAL_HIGHSCORE_ADDR_INT16),
        EepromManager::readInt16(EepromManager::EEPROM_FlappyBird_HARD_HIGHSCORE_ADDR_INT16)
    };
   
    String highscoreStrings[] = {
        String(highscores[0]),
        String(highscores[1]),
        String(highscores[2])
    };

    for (int i = 0; i < 3; i++) {
        if (highscores[i] < 10) {
            highscoreStrings[i] = "00" + highscoreStrings[i];
        } else if (highscores[i] < 100) {
            highscoreStrings[i] = "0" + highscoreStrings[i];
        }
    }

    display.setTextColor(TFT_DARKGREY);
    display.setTextSize(1);
    display.setFreeFont(FF26);
    display.drawString(highscoreStrings[0], 364, 146);
    display.drawString(highscoreStrings[1], 364, 206);
    display.drawString(highscoreStrings[2], 364, 266);

    highlightSelectedButton();
    DisplayManager::resetFont();
}

void LightsOutMenu::update() 
{
    
}

void LightsOutMenu::advanceSelectionDown()
{
    unhighlightSelectedButton();
    upCountMenuIndex();
    highlightSelectedButton();
}

void LightsOutMenu::advanceSelectionUp()
{
    unhighlightSelectedButton();
    downCountMenuIndex();
    highlightSelectedButton();
}

void LightsOutMenu::unhighlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(150, menuIndex*60 + 130, 180, 50, 10, TFT_WHITE);
    display.drawRoundRect(151, menuIndex*60 + 131, 178, 48, 8, TFT_WHITE);
}

void LightsOutMenu::highlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(150, menuIndex*60 + 130, 180, 50, 10, TFT_BLACK);
    display.drawRoundRect(151, menuIndex*60 + 131, 178, 48, 8, TFT_BLACK);
}

void LightsOutMenu::executeSelected()
{
    std::unique_ptr<Game> newGame(new FlappyBird(menuIndex));
    setCurrentGame(std::move(newGame));
}