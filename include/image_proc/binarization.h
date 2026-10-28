#ifndef BINARIZATION_H
#define BINARIZATION_H
#include <SDL2/SDL.h>

SDL_Surface *load_image(const char *path);
void load_grayscale(SDL_Surface *surface);
int otsu_threshold(SDL_Surface *surface);
void apply_threshold(SDL_Surface *surface, int seuil);

#endif

//Principe de load_grayscale : affiche l'image et convertit le rendu en gris

//Principe de otsu_threshold : trouve le seuil via un histogramme ( calcul de la moyenne pour un unique seuil )

//Principe de apply_threshold : par rapport à otsu , il prend ce seuil et l'intègre dans la fonction pour binariser l'image donc <= seuil renvoie noir sinon blanc

//Irfan view pour tester le tout (outil pour tester notre résultat)
