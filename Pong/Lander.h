#ifndef LANDER_H
#define LANDER_H

#include <raylib.h>
#include <string>
#include <iostream>

class Lander {
public:
	Lander(std::string cheminTextureP, std::string cheminTextureFlammeP , float xP, float yP);

	void load();
	void update(float dt);
	void draw();
	void unload();

	const float GRAVITE{ 20.0f };
	const float PROPULSION{ -45.0f };
	const float VITESSE_ROTATION { 2.0f };

	Texture2D texture;
	Texture2D textureFlamme;
	std::string cheminTexture { "" };
	std::string cheminTextureFlamme { "" };
	float x { 0.0f };
	float y { 0.0f };
	float vx { 0.0f };
	float vy { 0.0f };
	float rotation { -PI / 2.0f };
	Vector2 origine { 0.0f ,0.0f };
	Rectangle srcRect { 0.0f, 0.0f, 0.0f, 0.0f };
	Rectangle dstRect { 0.0f, 0.0f, 0.0f, 0.0f };

	bool flammeVisible { false };
};

#endif