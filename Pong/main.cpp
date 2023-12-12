#include <raylib.h>
const int LARGEUR_ECRAN = 800;
const int HAUTEUR_ECRAN = 450;

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
	SetTargetFPS(60);
}

void update()
{
	
}

void draw()
{
	
}

void unload()
{
	
}