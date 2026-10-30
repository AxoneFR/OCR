#include "../include/image_proc/binarization.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>

static Uint8 *get_pixel(SDL_Surface *surface, int x, int y)
{
    return (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
}

SDL_Surface *load_grayscale(const char *path)
{
    SDL_Surface *loaded = IMG_Load(path);
    if (loaded == NULL)
    {
        fprintf(stderr, "load_grayscale: impossible de charger %s (%s)\n", path, IMG_GetError());
        return NULL;
    }

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(loaded);
    if (surface == NULL)
    {
        fprintf(stderr, "load_grayscale: conversion impossible (%s)\n", SDL_GetError());
        return NULL;
    }

    for (int y = 0; y < surface->h; ++y)
    {
        for (int x = 0; x < surface->w; ++x)
        {
            Uint8 *p = get_pixel(surface, x, y);
            double gray = 0.299 * p[0] + 0.587 * p[1] + 0.114 * p[2];
            double alpha = p[3] / 255.0;
            Uint8 value = (Uint8)(gray * alpha + 255.0 * (1.0 - alpha));
            p[0] = value;
            p[1] = value;
            p[2] = value;
            p[3] = 255;
        }
    }
    return surface;
}

int otsu_threshold(SDL_Surface *surface)
{
    if (surface == NULL)
    {
        return 128;
    }

    unsigned int hist[256] = {0};
    for (int y = 0; y < surface->h; ++y)
    {
        for (int x = 0; x < surface->w; ++x)
        {
            hist[get_pixel(surface, x, y)[0]]++;
        }
    }
    unsigned int total = (unsigned int)surface->w * (unsigned int)surface->h;

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
        if (wB == 0)
        {
            continue;
        }
        wF = total - wB;
        if (wF == 0)
        {
            break;
        }

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

void apply_threshold(SDL_Surface *surface, int threshold)
{
    if (surface == NULL)
    {
        return;
    }

    for (int y = 0; y < surface->h; ++y)
    {
        for (int x = 0; x < surface->w; ++x)
        {
            Uint8 *p = get_pixel(surface, x, y);
            Uint8 value = (p[0] < threshold) ? 0 : 255;
            p[0] = value;
            p[1] = value;
            p[2] = value;
        }
    }
}


void remove_isolated(SDL_Surface *surface)
{
    if (surface == NULL)
    {
        return;
    }

    int width = surface->w;
    int height = surface->h;

    // We avoid touching the border so we keep it at y = 1
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            Uint8 *p = get_pixel(surface, x, y);

            // If black pixel
            if (p[0] == 0)
            {
                int white_neighbors = 0;

                // Check nearby neighbours if they are 8
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        if (dx == 0 && dy == 0){continue;}

                        Uint8 *neighbor = get_pixel(surface, x + dx, y + dy);
                        if (neighbor[0] == 255)
                        {
                            white_neighbors++;
                        }
                    }
                }


                if (white_neighbors == 8)
                {
                    p[0] = 255;
                    p[1] = 255;
                    p[2] = 255;
                }
            }
        }
    }
}
