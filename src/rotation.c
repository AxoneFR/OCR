#include "../include/image_proc/rotation.h"

#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <err.h>

SDL_Surface *rotate_image(SDL_Surface *src, double angle_degrees)
{
	if (src == NULL)
	{
		return NULL;
	}


	double radians = angle_degrees * M_PI / 180.0;
	double cos_theta = cos(radians);
	double sin_theta = sin(radians);

	int w = src->w;
	int h = src->h;

	SDL_Surface *dst = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, src->format->format);
	if (dst == NULL)
	{
		return NULL;
	}

	int cx = w / 2;
	int cy = h / 2;

	Uint32 *src_pixels = (Uint32 *)src->pixels;
	Uint32 *dst_pixels = (Uint32 *)dst->pixels;
	int src_pitch = src->pitch / 4;
	int dst_pitch = dst->pitch / 4;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			// Application de la matrice de rotation inverse
			// DEFAUT 2 : Plus proche voisin (pas d'interpolation), ce qui génère de l'aliasing (effet d'escalier).
			int x_orig = (int)(cos_theta * (x - cx) + sin_theta * (y - cy) + cx);
			int y_orig = (int)(-sin_theta * (x - cx) + cos_theta * (y - cy) + cy);

			// Vérification des limites de l'image source
			if (x_orig >= 0 && x_orig < w && y_orig >= 0 && y_orig < h)
			{
				dst_pixels[y * dst_pitch + x] = src_pixels[y_orig * src_pitch + x_orig];
			}
			else
			{
				// Remplissage des pixels vides par du blanc pur (fond de la grille)
				dst_pixels[y * dst_pitch + x] = 0xFFFFFFFF;
			}
		}
	}

	return dst;
}