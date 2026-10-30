#ifndef BINARIZATION_H
#define BINARIZATION_H
#include <SDL2/SDL.h>

SDL_Surface *load_grayscale(const char *path);
int otsu_threshold(SDL_Surface *surface);
void apply_threshold(SDL_Surface *surface, int seuil);
void remove_isolated(SDL_Surface *surface);

#endif

//Principe de load_grayscale : affiche l'image et convertit le rendu en gris

//Principe de otsu_threshold : trouve le seuil via un histogramme ( calcul de la moyenne pour un unique seuil )

//Principe de apply_threshold : par rapport à otsu , il prend ce seuil et l'intègre dans la fonction pour binariser l'image donc <= seuil renvoie noir sinon blanc

//Principe de remove_isolated : elimine les pixels noires isolés donc les pixels noires simple qui ont 8 voisins blanc ( bizarre mais tkt ).

//Irfan view pour tester le tout (outil pour tester notre résultat)
