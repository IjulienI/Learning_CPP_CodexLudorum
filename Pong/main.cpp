#include <raylib.h>
#include "Lander.h"
#include "SiteAtterissage.h"

const int LARGEUR_ECRAN = 800;
const int HAUTEUR_ECRAN = 450;
const int FPS = 60;
const float GRAVITE = 0.2f;

int etat = 0;

Lander lander{
	"assets/images/lander.png",LARGEUR_ECRAN / 2 , 0,true
};
SiteAtterissage siteAtterissage{
"assets/images/cible.png", 400, 400};

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
	siteAtterissage.load();
}

void update()
{
	float dt = GetFrameTime();
	if(etat == 0)
	{
		lander.update(dt);
	}
	else
	{
		if(IsKeyPressed(KEY_R)) etat = 0;
	}
}

void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	lander.draw();
	siteAtterissage.draw();

	EndDrawing();
}

void unload()
{
	lander.unload();
	siteAtterissage.unload();
	CloseWindow();
}