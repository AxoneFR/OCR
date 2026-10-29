#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "rotation.h"

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Utilisation : %s <image_entree.png> <angle>\n", argv[0]);
		return 1;
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur init SDL : %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface *img = IMG_Load(argv[1]);
	if (img == NULL)
	{
		printf("Erreur chargement image : %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	double angle = atof(argv[2]);

	SDL_Surface *rotated_img = rotate_image(img, angle);
	if (rotated_img == NULL)
	{
		printf("Erreur lors de la rotation\n");
		SDL_FreeSurface(img);
		SDL_Quit();
		return 1;
	}

	SDL_SaveBMP(rotated_img, "out_rotated.bmp");
	printf("Rotation effectuee avec succes ! Image sauvegardee sous out_rotated.bmp\n");

	SDL_FreeSurface(img);
	SDL_FreeSurface(rotated_img);
	SDL_Quit();

	return 0;
}