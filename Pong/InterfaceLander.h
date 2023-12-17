#ifndef INTERFACE_LANDER_H
#define INTERFACE_LANDER_H
#include <string>
#include "Lander.h"

class InterfaceLander
{
public:
    InterfaceLander(int xP, int yP, Lander& landerP);
    void update(float dt);
    void draw();

    const int SEPARATION_VERTICALE { 25 };

    Lander& lander;
    int x { 0 };
    int y { 0 };
    std::string libelleVx { "vx : 0 "};
    std::string libelleVy { "vy : 0 "};
    std::string libelleRotation { "angle : 0 "};
};
#endif