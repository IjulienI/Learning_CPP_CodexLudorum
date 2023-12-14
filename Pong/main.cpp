#include <functional>
#include <iostream>
#include <raylib.h>
#include <vector>
const int LARGEUR_ECRAN = 800;
const int HAUTEUR_ECRAN = 450;
const int TAILLE_BALLE = 16;
const int VITESSE_BALLE = 5;
const int LARGEUR_RAQUETTE = 75;
const int HAUTEUR_RAQUETTE = 15;
const int VITESSE_RAQUETTE = 6;
const int BRIQUE_LARGEUR = 100;
const int BRIQUE_HAUTEUR = 32;
const int BRIQUE_LIGNE = 8;
const int BRIQUE_COLONNES = 5;
const int BRIQUE_SEPARATEUR = 2;
const int VIE_DEPART = 3;

int vie = VIE_DEPART;
int nombreBriques = 0;

struct Brique
{
	Rectangle rect;
	bool visible = true;
};

std::vector<Brique> briques;

int vitesseBalleX = VITESSE_BALLE;
int vitesseBalleY = -VITESSE_BALLE;

Rectangle balle {100,200,TAILLE_BALLE,TAILLE_BALLE};
Rectangle raquette {100,HAUTEUR_ECRAN - HAUTEUR_RAQUETTE - 5,LARGEUR_RAQUETTE,HAUTEUR_RAQUETTE};
Rectangle rect { 0,0,BRIQUE_LARGEUR,BRIQUE_HAUTEUR};

void load();
void update();
void draw();
void unload();
bool collision(Rectangle a, Rectangle b);
void changeDirBall();

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
	for(int ligne = 0; ligne < BRIQUE_LIGNE;ligne++)
	{
		for(int colonnes = 0; colonnes < BRIQUE_COLONNES;colonnes++)
		{
			Brique brique = { { (float)BRIQUE_LARGEUR * ligne,(float)BRIQUE_HAUTEUR * colonnes,BRIQUE_LARGEUR - BRIQUE_SEPARATEUR,BRIQUE_HAUTEUR - BRIQUE_SEPARATEUR} };
			briques.push_back(brique);
			nombreBriques++;
		}
	}
}

void update()
{
	if(vie <= 0)
	{
		std::cout<<"GameOver";
	}
	else if(nombreBriques <= 0)
	{
		std::cout<<"Win !";
	}
	else
	{
		balle.x += vitesseBalleX;
		balle.y += vitesseBalleY;

		if(balle.x < 0)
		{
			vitesseBalleX *= -1;
		}
		else if(balle.x + TAILLE_BALLE > LARGEUR_ECRAN )
		{
			vitesseBalleX *= -1;
		}
		if(balle.y < 0)
		{
			vitesseBalleY *= -1;
		}
		else if(balle.y + TAILLE_BALLE > HAUTEUR_ECRAN)
		{
			vie--;
			vitesseBalleY *= -1;
			balle.x = raquette.x;
			balle.y = HAUTEUR_ECRAN / 2;
		}

		if(IsKeyDown(KEY_D))
		{
			raquette.x += VITESSE_RAQUETTE;
		}
		if(IsKeyDown(KEY_A))
		{
			raquette.x += -VITESSE_RAQUETTE;
		}

		if(raquette.x < 0)
		{
			raquette.x = 0;
		}
		else if(raquette.x + LARGEUR_RAQUETTE> LARGEUR_ECRAN)
		{
			raquette.x = LARGEUR_ECRAN - LARGEUR_RAQUETTE;
		}

		if(collision(balle,raquette))
		{
			changeDirBall();
		}

		for(Brique& brique : briques)
		{
			if(!brique.visible) continue;
			if(collision(brique.rect, balle))
			{
				vitesseBalleY *= -1;
				brique.visible = false;
				nombreBriques--;
			}			
		}
	}
	
}

void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	
	DrawRectangleRec(balle, WHITE);
	DrawRectangleRec(raquette, WHITE);
	for(Brique& brique : briques)
	{
		if(brique.visible == true) DrawRectangleRec(brique.rect, WHITE);
	}

	EndDrawing();
}

void unload()
{
	
}

bool collision(Rectangle a, Rectangle b)
{
	int xMinA = (int) a.x;
	int yMinA = (int) a.y;
	int xMaxA = (int) a.x + a.width;
	int yMaxA = (int) a.y + a.height;
	int xMinB = (int) b.x;
	int yMinB = (int) b.y;
	int xMaxB = (int) b.x + b.width;
	int yMaxB = (int) b.y + b.height;

	return(!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA));
}

void changeDirBall()
{
	balle.y = raquette.y - balle.height;
	vitesseBalleY = -vitesseBalleY;
}