#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include "TFT_eSPI.h"

namespace DisplayManager 
{
    extern TFT_eSPI tft;
    extern TFT_eSprite PillarSprite;

    void initialize();
    TFT_eSPI getDisplay();
}

#endif // DISPLAY_MANAGER_HPP