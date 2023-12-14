#include <raylib.h>
#include <string>
#include <fstream>
#include <sstream>

const int LARGEUR_ECRAN = 800;
const int HAUTEUR_ECRAN = 450;

std::string etat;
std::string description;
void load();
void update();
void draw();
void unload();
std::string changeDescription();
void ChangerEtat(std::string nouvelEtat);

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
	ChangerEtat("debut");
}

void update()
{
	if(etat == "debut")
	{
		if(IsKeyPressed(KEY_S))
		{
			ChangerEtat("sauter");
		}
		else if(IsKeyPressed(KEY_C))
		{
			ChangerEtat("cache");;
		}
	}
	else if(etat == "sauter")
	{
		if(IsKeyPressed(KEY_D))
		{
			ChangerEtat("dague");
		}
		else if(IsKeyPressed(KEY_A))
		{
			ChangerEtat("cache");
		}
	}
	else if(etat == "cache")
	{
		if(IsKeyPressed(KEY_D))
		{
			ChangerEtat("dague");
		}
		if(IsKeyPressed(KEY_F))
		{
			ChangerEtat("fuite");
		}
		if(IsKeyPressed(KEY_P))
		{
			ChangerEtat("pousser");
		}
	}
}

void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText(description.c_str(), 50, 20, 20, WHITE);
	EndDrawing();
}

void unload()
{
	
}

std::string changeDescription()
{
	std::string chemin = "textes/"+ etat + ".txt";
	std::ifstream fichier { chemin };
	std::stringstream tampon;
	tampon << fichier.rdbuf();
	return tampon.str();
	if(etat == "debut")
	{
		return 
		"Le magicien sort de l'ombre. Il jette sur vous un regard\n"
		"méprisant et ses doigts se crispent sur la sphère\n"
		"crépitante qu'il tient à la main\n"
		"- Vous introduire dans ma tour aura été votre dernière\n"
		"erreur, apprenti. \n"
		"Sa voix semble étrangement lointaine et ses yeux sont\n"
		"révulsés dans ses orbites. Vous comprenez avec horreur\n"
		"qu'il invoquait un sortilège mortel tendis qu'il vous\n"
		"parlait. Vous n'avez qu'un instant pour réagir\n"
		"\n"
		"S - Sauter sur le côté\n"
		"C - Vous cacher derrière un meuble";
	}
	else if(etat == "sauter")
	{
		return 
		"Vous sautez sur le côté au moment où le sortilège se\n"
		"déclenche. L'énergie magique vient exploser à l'endroit\n"
		"où vous vous touviez l'instant précédent. Vous courrez\n"
		"pour mettre un peux de distance entre le magicien et vous.\n"
		"Vous avisez une dague posée sur un bureau plus loin\n"
		"et une grosse armoire derrière laquelle vous pourriez\n"
		"vous cacher\n\n"
		"D - Allez ramasser la dague\n"
		"A - Vous cacher derrière l'armoire\n";
	}
	else if(etat == "cache")
	{
		return 
		"Bonsoir !\n\n"
		"D - Aller ramasser la dague\n"
		"F - Foncer vers la sortie\n"
		"P - Pousser l'armoire sur le magicien\n";
	}
}

void ChangerEtat(std::string nouvelEtat)
{
	etat = nouvelEtat;
	description = changeDescription();
}