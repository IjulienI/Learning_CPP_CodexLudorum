#include <raylib.h>
#include "Lander.h"

const int LARGEUR_ECRAN = 800;
const int HAUTEUR_ECRAN = 450;
const int FPS = 60;
const float GRAVITE = 0.2f;

Lander lander{
	"assets/images/lander.png","assets/images/lander-flamme.png",LARGEUR_ECRAN / 2 , 0
};

void load();
void update();
void draw();
void unload();

int main() {
	load();
	while (!WindowShouldClose()) {
		update();
		draw();
	}
	unload();
	return 0;
}

void load()
{
	InitWindow(LARGEUR_ECRAN,HAUTEUR_ECRAN,"NoEngine");
	SetTargetFPS(FPS);
	lander.load();
}

void update()
{
	float dt = GetFrameTime();
	lander.update(dt);
}

void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	lander.draw();

	EndDrawing();
}

void unload()
{
	lander.unload();
	CloseWindow();
}