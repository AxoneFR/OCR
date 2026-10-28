#include "../include/image_proc/binarization.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    const char *img_path = "C:/Users/anhkh/Pictures/Saved Pictures/2 euros.png";

    SDL_Surface *img = load_grayscale(img_path);
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

    SDL_FreeSurface(img);
    return 0;
}
