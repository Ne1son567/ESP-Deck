
#ifndef Pillar_HPP
#define Pillar_HPP

#include <TFT_eSPI.h>
#include <vector>

class Pillar {
private:
    int xPos;
    int yPos;
    int gap;
    int step;
    int xSize;
    int ySize;
    int openingXSize;
    int openingYSize;
    
    TFT_eSprite UpperPillarSprite;
    TFT_eSprite LowerPillarSprite;

    
public:
   
    Pillar(int _xSize);
    void updatePillar();
    void gameOverAnimation();
    int getXPos();
    int getYPosAbove();
    int getYPosBelow();
    int getXSize();
    int getYSize();
    
};

#endif
