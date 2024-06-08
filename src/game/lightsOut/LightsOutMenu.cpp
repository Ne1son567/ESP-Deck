
#include "bitmap/TrophyGoldenBitmap.hpp"
#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/lightsOut/LightsOutMenu.hpp"
#include "game/lightsOut/LightsOut.hpp"
#include "bitmap/lightsOut/LightsOutBackgroundBitmap.hpp"
#include "font/Fonts.hpp"
#include "display/DisplayManager.hpp"
#include <game/menu/Menu.hpp>
#include "eeprom/EepromManager.hpp"

LightsOutMenu::LightsOutMenu()
{

}

void LightsOutMenu::renderMenu()
{
    menuIndex = 0;
    menuButtonAmount = 2;

    TFT_eSPI& display = DisplayManager::getDisplay();
    backgroundSprite.pushImage(-60, -1, 480, 320, lightsOutBackgroundBitmap);
    
    backgroundSprite.pushSprite(60, 1);

    display.setFreeFont(FF32);
    display.setTextSize(1);
    display.setTextColor(TFT_WHITE);
    display.drawString("LightsOut", 145, 40);
    
    display.fillRoundRect(150, 130, 200, 50, 10, TFT_LIGHTGREY);
    display.drawString("Possible", 150, 139);

    display.fillRoundRect(150, 210, 200, 50, 10, TFT_LIGHTGREY);
    display.drawString("Difficult", 160, 219);

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
    display.drawRoundRect(150, menuIndex*80 + 130, 200, 50, 10, TFT_LIGHTGREY);
    display.drawRoundRect(151, menuIndex*80 + 131, 198, 48, 8, TFT_LIGHTGREY);
}

void LightsOutMenu::highlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(150, menuIndex*80 + 130, 200, 50, 10, TFT_WHITE);
    display.drawRoundRect(151, menuIndex*80 + 131, 198, 48, 8, TFT_WHITE);
}

void LightsOutMenu::executeSelected()
{
    std::unique_ptr<Game> newGame(new LightsOut(menuIndex));
    setCurrentGame(std::move(newGame));
}