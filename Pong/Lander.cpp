#include "Lander.h"
#include <math.h>

Lander::Lander(std::string cheminTextureP,std::string cheminTextureFlammeP, float xP, float yP) :
	cheminTexture{ cheminTextureP },
	cheminTextureFlamme{cheminTextureFlammeP},
	x{ xP },
	y{ yP }
{

}


void Lander::load()
{
	texture = LoadTexture(cheminTexture.c_str());
	textureFlamme = LoadTexture(cheminTextureFlamme.c_str());
	origine = { (float)(texture.width / 2), (float)(texture.height / 2) };
	srcRect = { 0.0f ,0.0f, (float)texture.width, (float)texture.height };
}

void Lander::update(float dt)
{
	if (IsKeyDown(KEY_SPACE)) {
		vx += std::cos(rotation) * std::abs(PROPULSION) * dt;
		vy += std::sin(rotation) * std::abs(PROPULSION) * dt;
		flammeVisible = true;
	}
	else {
		flammeVisible = false;
	}
	if (IsKeyDown(KEY_A)) {
		rotation -= VITESSE_ROTATION * dt;
	}
	else if (IsKeyDown(KEY_D)) {
		rotation += VITESSE_ROTATION * dt;
	}
	vy += GRAVITE * dt;
	x += vx * dt;
	y += vy * dt;
}

void Lander::draw()
{
	float rotationDegres = rotation * 180 / PI;
	dstRect = { x, y, (float)texture.width, (float)texture.height };

	DrawTexturePro(texture, srcRect,dstRect,origine,rotationDegres, WHITE);
	if (flammeVisible) {
		DrawTexturePro(textureFlamme, srcRect, dstRect, origine, rotationDegres, WHITE);
	}
}

void Lander::unload()
{
	UnloadTexture(texture);
	UnloadTexture(textureFlamme);
}
