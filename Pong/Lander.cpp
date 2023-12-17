#include "Lander.h"
#include <math.h>

Lander::Lander(std::string cheminTextureP, float xP, float yP, bool centreP) :
Sprite{cheminTextureP,xP,yP,-PI/2.0f, centreP}
{

}

void Lander::update(float dt)
{
	if (IsKeyDown(KEY_SPACE)) {
		vx += cos(rotation) * std::abs(PROPULSION) * dt;
		vy += sin(rotation) * std::abs(PROPULSION) * dt;
		flammeVisible = true;
	}
	else {
		flammeVisible = false;
	}
	if (IsKeyDown(KEY_A)) {
		rotation -= VITESSE_ROTATION * dt;
		if(rotation < 0.0f)
		{
			rotation = 2 * PI + rotation;
		}
	}
	else if (IsKeyDown(KEY_D)) {
		rotation += VITESSE_ROTATION * dt;
		if(rotation < 2 * PI)
		{
			rotation = rotation - 2 * PI;
		}
	}
	vy += GRAVITE * dt;
	x += vx * dt;
	y += vy * dt;

	flamme.x = x;
	flamme.y = y;
	flamme.rotation = rotation;
	flamme.visible = flammeVisible;
}

void Lander::load()
{
	Sprite::load();
	flamme.load();
}

void Lander::draw()
{
	Sprite::draw();
	flamme.draw();
}

void Lander::unload()
{
	Sprite::unload();
	flamme.unload();
}

bool Lander::atterrissageOk()
{
	int rotation360 = rotationDegres360();
	return abs(vy) < MAX_VY && abs(vx) < MAX_VX && ((rotation360 < MAX_ROTATION_DEGRES) || (rotation360 > 360 - MAX_ROTATION_DEGRES));
}

std::string Lander::formaterVx(float vx)
{
	std::string valeurVx {""};
	if(vx < 0.0f)
	{
		valeurVx = std::to_string(vx).substr(0,6);
	}
	else
	{
		valeurVx = std::to_string(vx).substr(0,5);
	}
	std::string texteVx = "vx :" + valeurVx;
	return texteVx;
}

std::string Lander::formaterVy(float vy)
{
	std::string valeurVy {""};
	if(vy < 0.0f)
	{
		valeurVy = std::to_string(vy).substr(0,6);
	}
	else
	{
		valeurVy = std::to_string(vy).substr(0,5);
	}
	std::string texteVy = "vy :" + valeurVy;
	return texteVy;
}

int Lander::rotationDegres360()
{
	float rotationAjustee = rotation + PI / 2.0f;
	float rotationDegres = rotationAjustee * 180 / PI;
	int rotationArrondie = round(rotationDegres);
	int rotation360 = rotationArrondie %360;
	return rotation360;
}
