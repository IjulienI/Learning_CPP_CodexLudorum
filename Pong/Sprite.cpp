#include "Sprite.h"

Sprite::Sprite(std::string CheminTextureP, float xP, float yP, float rotationP, bool centreP):
cheminTexture(CheminTextureP),
x {xP},
y {yP},
rotation { rotationP},
centre { centreP}
{
    
}

void Sprite::load()
{
    texture = LoadTexture(cheminTexture.c_str());
    if(centre)
    {
        origine = {(float)(texture.width)/2,(float)(texture.height)/2};
    }
    srcRect = {0.0f,0.0f,(float)texture.width, (float)texture.height};
}

void Sprite::draw()
{
    if(visible)
    {
        float rotationDegres = rotation * 180 / PI;
        dstRect = {x,y,(float)texture.width, (float)texture.height};
        DrawTexturePro(texture, srcRect,dstRect,origine,rotationDegres, WHITE);
    }
}

void Sprite::unload()
{
    UnloadTexture(texture);
}

Rectangle Sprite::getRectangle()
{
    Rectangle rect {x - origine.x, y - origine.y , (float) texture.width, (float) texture.height};
    return rect;
}

