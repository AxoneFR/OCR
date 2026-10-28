#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double w_hidden[2][2];
    double b_hidden[2]; 

    double w_output[2]; 
    double b_output; 

    double hidden[2]; 
    double output; 
} Network;

double sigmoid(double x);
double sigmoid_prime(double y);
double init_weight();
void init_network(Network *net);
void forward(Network *net, double input[2]);
void train(Network *net, double input[2], double target, double lr);

#endif