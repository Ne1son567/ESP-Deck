#ifndef Main_HPP
#define Main_HPP

#include <vector>

extern bool upbutton;
void createPillar();
void deletePillar();
void displayInitialize();
void inputLoop(void * parameter);
void restard();
void gameOver();
std::vector<unsigned short> flipImage180(const unsigned short* imageData, int width, int height);

#endif