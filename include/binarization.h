#ifndef OCR_BINARIZATION_H
#define OCR_BINARIZATION_H

unsigned char *load_grayscale(const char *path, int *width, int *height)
{
	int channels_in_file;
	unsigned char *img = stbi_load(path, width, height, &channels_in_file, 1);
	return img;
}

int otsu_threshold(const unsigned char *img, int width, int height);

void apply_threshold(unsigned char *img, int width, int height, int seuil);



#endif

//Principe de load_grayscale : affiche l'image et convertit le rendu en gris

//Principe de otsu_threshold : trouve le seuil via un histogramme ( calcul de la moyenne pour un unique seuil )

//Principe de apply_threshold : par rapport à otsu , il prend ce seuil et l'intègre dans la fonction pour binariser l'image donc <= seuil renvoie noir sinon blanc

//Irfan view pour tester le tout (outil pour tester notre résultat)