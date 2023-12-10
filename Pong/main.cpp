#include <raylib.h>
#include <iostream>
#include <string>

//Declarations
//----------------------------------------------------------------

const int LARGEUR_ECRAN = 800;
const int HAUTEUR_ECRAN = 450;
const int VITESSE_RAQUETTE_GAUCHE = 4;
const int VITESSE_RAQUETTE_DROITE = 4;
const int VITESSE_BALLE = 5;
const int POINTS_POUR_MATCH = 7;
const int HAUTEUR_RAQUETTE = 128;
const int LARGEUR_RAQUETTE = 32;
const int TAILLE_BALLE = 32;

Sound hit;
Sound defeat;
Sound win;
Sound wallTouched;

Rectangle balle {50, 100, TAILLE_BALLE, TAILLE_BALLE};
int vitesseBalleX = VITESSE_BALLE;
int vitesseBalleY = -VITESSE_BALLE;

Rectangle raquetteGauche { 0, 100 , LARGEUR_RAQUETTE, HAUTEUR_RAQUETTE};
int vitesseRaquetteGauche = VITESSE_RAQUETTE_GAUCHE;

Rectangle raquetteDroite { LARGEUR_ECRAN - 32, 100, LARGEUR_RAQUETTE, HAUTEUR_RAQUETTE};
int vitesseRaquetteDroite = VITESSE_RAQUETTE_DROITE;

int scoreGauche = 0;
int scoreDroite = 0;

int etatJeu = 0;
bool endGame;

void load();
void update();
void draw();
void unload();
bool collision(Rectangle a , Rectangle b);
void rebondSurLaRaquette(bool coteJoueur);
void relancerBalle(bool coteJoueur);

//Code et definitions
//----------------------------------------------------------------

int main() {
	load();
	while (!WindowShouldClose()) {
		update();
		draw();
	}
	unload();
	return 0;
}

//Chargement du jeu

void load() {
	InitWindow(LARGEUR_ECRAN, HAUTEUR_ECRAN, "NoEngine");
	SetTargetFPS(60);
	InitAudioDevice();

	hit = LoadSound("hit.wav");
	defeat = LoadSound("defeat.wav");
	wallTouched = LoadSound("wall.wav");
	win = LoadSound("win.wav");
}

//Mise a jour de l'univers

void update(){

	//Movements balle
	if(etatJeu == 0)
	{
		balle.x = balle.x + vitesseBalleX;
		balle.y = balle.y + vitesseBalleY;

	} else
	{
		endGame = true;
		if(IsKeyDown(KEY_R))
		{
			scoreDroite = 0;
			scoreDroite = 0;
			etatJeu = 0;
			balle.x = LARGEUR_ECRAN / 2 - balle.width /2;
			balle.y = HAUTEUR_ECRAN / 2 + balle.height / 2;
			endGame = false;
		}
	}
	
	if(balle.y < 0 )
	{
		vitesseBalleY = -vitesseBalleY;
		balle.y = 0;
		PlaySound(hit);
	}
	if(balle.y + balle.height> HAUTEUR_ECRAN)
	{
		vitesseBalleY = -vitesseBalleY;
		balle.y = HAUTEUR_ECRAN - balle.height;
		PlaySound(hit);
	}

	//Movemements Raquette
	if(IsKeyDown(KEY_S))
	{
		raquetteGauche.y = raquetteGauche.y + vitesseRaquetteGauche;
	}
	else if (IsKeyDown(KEY_W))
	{
		raquetteGauche.y = raquetteGauche.y - vitesseRaquetteGauche;
	}

	//IA
	if(balle.y < raquetteDroite.y + raquetteDroite.height / 4)
	{
		raquetteDroite.y = raquetteDroite.y - vitesseRaquetteDroite;
	}
	else if(balle.y > raquetteDroite.y + raquetteDroite.height * 3 / 4)
	{
		raquetteDroite.y = raquetteDroite.y + vitesseRaquetteDroite;
	}

	//Bloquage raquette
	if(raquetteGauche.y < 0)
	{
		raquetteGauche.y = 0;
	}
	if(raquetteGauche.y + raquetteGauche.height > HAUTEUR_ECRAN)
	{
		raquetteGauche.y = HAUTEUR_ECRAN - raquetteGauche.height;
	}

	if(raquetteDroite.y < 0)
	{
		raquetteDroite.y = 0;
	}
	if(raquetteDroite.y + raquetteDroite.height > HAUTEUR_ECRAN)
	{
		raquetteDroite.y = HAUTEUR_ECRAN - raquetteDroite.height;
	}

	//Colision
	if(collision(raquetteGauche, balle))
	{
		rebondSurLaRaquette(true);
	}
	else if(collision(raquetteDroite, balle))
	{
		rebondSurLaRaquette(false);
	}

	//Sortie de terrain
	if(balle.x < 0)
	{
		scoreDroite++;
		relancerBalle(true);
		if(scoreDroite >= POINTS_POUR_MATCH)
		{
			etatJeu = 2;
			PlaySound(defeat);
		}
	}
	if(balle.x + balle.width > LARGEUR_ECRAN)
	{
		scoreGauche++;
		relancerBalle(false);
		if(scoreGauche >= POINTS_POUR_MATCH )
		{
			etatJeu = 1;
			PlaySound(win);
		}
	}
}

//Dessin de l'univers

void draw() {
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText(std::to_string(scoreGauche).c_str(),300,50,20,LIGHTGRAY);
	DrawText(std::to_string(scoreDroite).c_str(),500,50,20,LIGHTGRAY);

	if(endGame)
	{
		if(etatJeu == 1)
		{
			DrawText("YOU WIN",250,200,50,LIGHTGRAY);
		}else
		{
			DrawText("GAME OVER",250,200,50,LIGHTGRAY);
		}
	}

	DrawRectangleRec(balle,WHITE);
	DrawRectangleRec(raquetteGauche, WHITE);
	DrawRectangleRec(raquetteDroite, WHITE);

	EndDrawing();
}

//Dechargement du jeu 

void unload() {
	CloseWindow();
}

//Collisions
bool collision(Rectangle a, Rectangle b)
{
	int xMinA = (int)(a.x);
	int yMinA = (int)(a.y);
	int xMaxA = (int)(a.x + a.width);
	int yMaxA = (int)(a.y + a.height);
	int xMinB = (int)(b.x);
	int yMinB = (int)(b.y);
	int xMaxB = (int)(b.x + b.width);
	int yMaxB = (int)(b.y + b.height);
	
	return (!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA));
}

void rebondSurLaRaquette(bool coteJoueur)
{
	vitesseBalleX = - vitesseBalleX;
	if(coteJoueur)
	{
		balle.x = raquetteGauche.x + raquetteGauche.width;
	} else
	{
		balle.x = raquetteDroite.x - raquetteDroite.width;
	}
	PlaySound(hit);
}

void relancerBalle(bool coteJoueur)
{
	if(coteJoueur)
	{
		balle.x = 50;
	} else
	{
		balle.x = LARGEUR_ECRAN - 50;
	}
	balle.y = 100;
	vitesseBalleX = -vitesseBalleX;
	PlaySound(wallTouched);
}
