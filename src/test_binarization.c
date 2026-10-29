#include "../include/image_proc/binarization.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <image>\n", argv[0]);
        return 1;
    }

    SDL_Surface *img = load_grayscale(argv[1]);
    if (img == NULL)
    {
        return 1;
    }
    
    printf("Image chargee : %dx%d (niveaux de gris)\n", img->w, img->h);
    IMG_SavePNG(img, "out_gray.png");

    int threshold = otsu_threshold(img);
    printf("Seuil Otsu : %d\n", threshold);

    apply_threshold(img, threshold);
    IMG_SavePNG(img, "out_binaire.png");

	remove_isolated(img); // Répare les degats
    IMG_SavePNG(img, "out_cleaned.png");
    printf("Suppression du bruit appliquee et sauvegardee : out_cleaned.png\n");

    SDL_FreeSurface(img);
    return 0;
}
