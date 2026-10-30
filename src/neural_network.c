#include "../include/neural_network/neural_network.h"

// take x and put it in the interval ]0,1[
double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}

// derivate of sigmoid
double sigmoid_prime(double y){
    return y * (1.0 - y);
}

double init_weight(){
    return ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
}

// 2-2-1
void init_network(Network *net){

    for (int i = 0; i < 2; i++) {
        net->b_hidden[i] = init_weight();
        for (int j = 0; j < 2; j++) {
            net->w_hidden[i][j] = init_weight();
        }
    }

    for (int i = 0; i < 2; i++) {
        net->w_output[i] = init_weight();
    }
    net->b_output = init_weight();
}

void forward(Network *net, double input[2]) {
    
    //hidden part
    for (int i = 0; i < 2; i++) {
        double sum = net->b_hidden[i];
        for (int j = 0; j < 2; j++) {
            sum += input[j] * net->w_hidden[i][j];
        }
        net->hidden[i] = sigmoid(sum);
    }

    //output part
    double sum_out = net->b_output;
    for (int i = 0; i < 2; i++) {
        sum_out += net->hidden[i] * net->w_output[i];
    }
    net->output = sigmoid(sum_out);
}

void train(Network *net, double input[2], double target, double lr){
    forward(net, input);

    double d_output = (net->output - target) * sigmoid_prime(net->output);

    double d_hidden[2];
    for (int i = 0; i < 2; i++) {
        d_hidden[i] = (d_output * net->w_output[i]) * sigmoid_prime(net->hidden[i]);
    }

    for (int i = 0; i < 2; i++) {
        net->w_output[i] -= lr * d_output * net->hidden[i];
    }
    net->b_output -= lr * d_output;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            net->w_hidden[i][j] -= lr * d_hidden[i] * input[j];
        }
        net->b_hidden[i] -= lr * d_hidden[i];
    }
}

int main(){

    srand(time(NULL));

    Network net;
    init_network(&net);

    double inputs[4][2] = { {0,0}, {0,1}, {1,0}, {1,1}};
    double targets[4] = {1, 0, 0, 1};

    double lr = 0.2;
    int epochs = 1000000000;

    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int i = 0; i < 4; i++) {
            train(&net, inputs[i], targets[i], lr);
        }
    }

    printf("--- Résultats après entraînement ---\n");
    for (int i = 0; i < 4; i++) {
        forward(&net, inputs[i]);
        printf("Entrée : [%.0f, %.0f] -> Sortie attendue : %.0f | Prédiction : %.4f (Arrondi : %d)\n",
               inputs[i][0], inputs[i][1], targets[i], net.output, net.output > 0.5 ? 1 : 0);
    }

    return EXIT_SUCCESS;
}
