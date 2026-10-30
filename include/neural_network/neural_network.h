#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define SAVED_N_DIR "include/saved_networks/"

#define NB_SAMPLES  4 // ???

#define NB_INPUTS   2
#define NB_HIDDEN   2
#define NB_OUTPUTS  1 

// #define NB_INPUTS   784
// #define NB_HIDDEN   128
// #define NB_OUTPUTS  26

// use a 2->2->1 MLP format for a XNOR door
// use a 784->128->26 MLP format for a letter recognition

typedef struct {
    double w_hidden[NB_HIDDEN][NB_INPUTS];
    double b_hidden[NB_HIDDEN]; 

    double w_output[NB_OUTPUTS][NB_HIDDEN]; 
    double b_output[NB_OUTPUTS]; 

    double hidden[NB_HIDDEN]; 
    double output[NB_OUTPUTS]; 
} Network;

double sigmoid(double x);
double sigmoid_prime(double y);
double random_weight();

void init_network(Network *net);
void forward(Network *net, double input[NB_INPUTS]);

void train(Network *net, double input[NB_INPUTS], double target[NB_OUTPUTS], double lr);
void complete_train(Network *net, int epochs, double lr, double **inputs, double **targets);

int save_network(Network *net, char *path);
Network *load_network(char *path);

void test_results(Network *net, int nb_samples, double **inputs, double **targets);
void show_wb(Network *net);

int predict_xnor(Network *net, double input[NB_INPUTS]);
char predict_char(Network *net, double *input);

#endif