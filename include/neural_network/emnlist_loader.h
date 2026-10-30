#ifndef EMNIST_LOADER_H
#define EMNIST_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

// the EMNIST dataset contains thousands of images of letters written in 28*28px 

#define IMG_SIZE 784 // 28 * 28px
#define NB_CLASSES 26

typedef struct {
    int count;
    double **inputs;
    double **targets;

} Dataset;

Dataset *load_emnist_dataset(const char *image_path, const char *label_path, int max_samples);
void free_dataset(Dataset *dataset);

#endif