#include "../include/neural_network/emnlist_loader.h"

Dataset *load_emnist_dataset(const char *image_path, const char *label_path, int max_samples){

    FILE *image_file = fopen(image_path, "rb");
    FILE *label_file = fopen(label_path, "rb");

    if (!image_file || !label_file){
        if(image_file) fclose(image_file);
        if(label_file) fclose(label_file);
        return NULL;
    }

    // skip metadata of 16B and 8B respectively
    fseek(image_file, 16, SEEK_SET);
    fseek(label_file, 8, SEEK_SET);

    Dataset *dataset = malloc(sizeof(Dataset));

    dataset->count = max_samples;
    dataset->inputs = malloc(max_samples * sizeof(double *));
    dataset->targets = malloc(max_samples * sizeof(double *));
    
    uint8_t raw_pixels[IMG_SIZE];
    uint8_t label;

    for (int i = 0; i < max_samples; i++) {
        dataset->inputs[i] = malloc(IMG_SIZE * sizeof(double));
        dataset->targets[i] = calloc(NB_CLASSES, sizeof(double));

        if (fread(raw_pixels, sizeof(uint8_t), IMG_SIZE, image_file) != IMG_SIZE ||
            fread(&label, sizeof(uint8_t), 1, label_file) != 1){
            dataset->count = i;
            break;
        }

        for (int r = 0; r < 28; r++) {
            for (int c = 0; c < 28; c++) {
                uint8_t p = raw_pixels[c * 28 + (27 - r)];
                dataset->inputs[i][r * 28 + c] = (double)p / 255.0;
            }
        }

        int class_idx = label - 1;
        if (class_idx >= 0 && class_idx < NB_CLASSES) {
            dataset->targets[i][class_idx] = 1.0;
        }
    }

    fclose(image_file);
    fclose(label_file);
    return dataset;
}

void free_dataset(Dataset *dataset) {
    if (!dataset) return;

    for (int i = 0; i < dataset->count; i++) {
        free(dataset->inputs[i]);
        free(dataset->targets[i]);
    }

    free(dataset->inputs);
    free(dataset->targets);
    free(dataset);
}