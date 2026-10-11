#include "binarization.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	const char *img_path = "C:/Users/anhkh/Pictures/Saved Pictures/2 euros.png";

	int width, height, channels_in_file;
	unsigned char *img = stbi_load(img_path, &width, &height, &channels_in_file, 1);

	assert(img != NULL && "Image non trouvee");

	printf("Image chargee : %dx%d (niveaux de gris)\n", width, height);

	stbi_write_png("out_gray.png", width, height, 1, img, width);

	stbi_image_free(img);
	return 0;
}

