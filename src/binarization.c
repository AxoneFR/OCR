#include "binarization.h"

#include <stddef.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char *load_grayscale(const char *path, int *width, int *height)
{
	int channels_in_file = 0;
	unsigned char *img = stbi_load(path, width, height, &channels_in_file, 1);
	if (img == NULL)
	{
		fprintf(stderr, "load_grayscale: impossible de charger %s (%s)\n",path, stbi_failure_reason());
	}
	return img;
}


int otsu_threshold(const unsigned char *img, int width, int height)
{
	if (img == NULL)
	{
		return 128;
	}

	unsigned int hist[256] = {0};
	size_t n = (size_t)width * (size_t)height;
	for (size_t i = 0; i < n; ++i)
	{
		hist[img[i]]++;
	}
	unsigned int total = (unsigned int)n;

	double sum = 0.0;
	for (int t = 0; t < 256; ++t)
	{
		sum += t * (double)hist[t];
	}

	double sumB = 0.0;
	unsigned int wB = 0;
	unsigned int wF = 0;
	double varMax = -1.0;
	int threshold = 128;

	for (int t = 0; t < 256; ++t)
	{
		wB += hist[t];
		if (wB == 0) continue;
		wF = total - wB;
		if (wF == 0) break;

		sumB += t * (double)hist[t];
		double mB = sumB / wB;
		double mF = (sum - sumB) / wF;

		double varBetween = (double)wB * (double)wF * (mB - mF) * (mB - mF);
		if (varBetween > varMax)
		{
			varMax = varBetween;
			threshold = t;
		}
	}
	return threshold;
}

void apply_threshold(unsigned char *img, int width, int height, int threshold);