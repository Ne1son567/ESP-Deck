
#ifndef Pillar_HPP
#define Pillar_HPP

#include <TFT_eSPI.h>
#include <vector>

class Pillar {
private:
    int xPos;
    int yPos;
    int gap;
    int xImageSize;
    int yImageSize;
    
    TFT_eSprite UpperPillarSprite;
    TFT_eSprite LowerPillarSprite;

    
public:
   
    Pillar(int _xPos);
    void updatePillar();
    int getXPos();
    // Funktion zum Flippen eines Bildes
    static std::vector<unsigned short> flipImage180(const unsigned short* imageData, int width, int height);
};

#endif
