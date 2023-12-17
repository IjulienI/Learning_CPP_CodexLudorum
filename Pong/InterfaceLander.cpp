#include "InterfaceLander.h"
#include <raylib.h>

InterfaceLander::InterfaceLander(int xP, int yP, Lander& landerP):
x {xP},
y {yP},
lander {landerP}
{
    
}

void InterfaceLander::update(float dt)
{
    libelleVx = "vx : " + std::to_string(lander.vx);
    libelleVy = "vy : " + std::to_string(lander.vy);
    libelleRotation = "rotation : " + std::to_string(lander.rotation);
}

void InterfaceLander::draw()
{
    DrawText(libelleVx.c_str(),x,y,10,WHITE);
    DrawText(libelleVy.c_str(), x, y + SEPARATION_VERTICALE, 10, WHITE);
    DrawText(libelleRotation.c_str(), x, y + SEPARATION_VERTICALE * 2, 10, WHITE);
}

std::string InterfaceLander::formaterRotation(int rotationDegres)
{
    
}
