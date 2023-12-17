#ifndef SITE_ATTERISSAGE_H
#define SITE_ATTERISSAGE_H

#include <raylib.h>
#include <string>

#include "Sprite.h"

class SiteAtterissage : public Sprite
{
public:
    SiteAtterissage(std::string cheminTextureP, float xP, float yP);
};

#endif

