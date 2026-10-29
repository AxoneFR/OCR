#include "../include/neural_network/neural_network.h"

// take x and put it in the interval ]0,1[
double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_prime(double y){
    return y * (1.0 - y);
}

double random_weight(){
    return ((double)rand() / (double)RAND_MAX) - 0.5; //  * 2.0 - 1.0
}

void init_network(Network *net){

    for (int i = 0; i < NB_HIDDEN; i++) {
        net->b_hidden[i] = random_weight();
        for (int j = 0; j < NB_INPUTS; j++) {
            net->w_hidden[i][j] = random_weight();
        }
    }

    for (int i = 0; i < NB_OUTPUTS; i++) {
        for (int j = 0; j < NB_HIDDEN; j++)
        {
            net->w_output[i][j] = random_weight();
        }
    }

    for (int i = 0; i < NB_OUTPUTS; i++){
        net->b_output[i] = random_weight();
    }
}

void forward(Network *net, double input[NB_INPUTS]) {
    
    //hidden part
    for (int i = 0; i < NB_HIDDEN; i++) {
        double sum = net->b_hidden[i];
        for (int j = 0; j < NB_INPUTS; j++) {
            sum += input[j] * net->w_hidden[i][j];
        }
        net->hidden[i] = sigmoid(sum);
    }

    //output part
    for (int i = 0; i < NB_OUTPUTS; i++) {

        double sum_out = net->b_output[i];
        for (int j = 0; j < NB_HIDDEN; j++){

            sum_out += net->hidden[j] * net->w_output[i][j];
        }

        net->output[i] = sigmoid(sum_out);
    }
}

void train(Network *net, double input[NB_INPUTS], double target[NB_OUTPUTS], double lr){
    forward(net, input);

    // backpropagation : we measure the errors from the output to the input
    double d_output[NB_OUTPUTS];
    for (int i = 0; i < NB_OUTPUTS; i++){
        d_output[i] = (net->output[i] - target[i]) * sigmoid_prime(net->output[i]);
    }

    double d_hidden[NB_HIDDEN];
    for (int i = 0; i < NB_HIDDEN; i++) {

        double error = 0.0;
        for (int j = 0; j < NB_OUTPUTS; j++){
            error += (d_output[j] * net->w_output[j][i]);
        }
        d_hidden[i] = error * sigmoid_prime(net->hidden[i]);
    }

    // descente de gradient : update of the weights and biases
    for (int i = 0; i < NB_OUTPUTS; i++) {

        for (int j = 0; j < NB_HIDDEN; j++){
            net->w_output[i][j] -= lr * d_output[i] * net->hidden[j];
        }
        net->b_output[i] -= lr * d_output[i];   
    }

    for (int i = 0; i < NB_HIDDEN; i++) {
        for (int j = 0; j < NB_INPUTS; j++) {
            net->w_hidden[i][j] -= lr * d_hidden[i] * input[j];
        }
        net->b_hidden[i] -= lr * d_hidden[i];
    }
}

void show_results(Network *net, double inputs[NB_SAMPLES][NB_INPUTS], double targets[NB_SAMPLES][NB_OUTPUTS]) {
    printf("--- Résultats après entraînement ---\n");
    for (int i = 0; i < NB_SAMPLES; i++) {
        forward(net, inputs[i]);
        printf("Entrée %d : ", i);
        for (int k = 0; k < NB_OUTPUTS; k++) {
            printf("Sortie attendue : %.0f | Prédiction : %.4f (Arrondi : %d) ",
                   targets[i][k], net->output[k], net->output[k] > 0.5 ? 1 : 0);
        }
        printf("\n");
    }

    printf("--- Affichage des poids & biais ---\n");

    for (int i = 0; i < NB_HIDDEN; i++) {
        for (int j = 0; j < NB_INPUTS; j++) {
            printf("poids du noeud [%d,%d] caché : %f\n", i, j, net->w_hidden[i][j]);
        }
    }
    for (int j = 0; j < NB_HIDDEN; j++) {
        printf("biais du noeud %d caché : %f\n", j, net->b_hidden[j]);
    }
    for (int i = 0; i < NB_OUTPUTS; i++) {
        for (int j = 0; j < NB_HIDDEN; j++) {
            printf("poids de sortie [%d,%d] : %f\n", i, j, net->w_output[i][j]);
        }
        printf("biais du noeud %d de sortie : %f\n", i, net->b_output[i]);
    }
}

void complete_train(Network *net, int epochs, double lr, double inputs[NB_SAMPLES][NB_INPUTS], double targets[NB_SAMPLES][NB_OUTPUTS]){

    for (int step = 0; step < epochs; step++) {
        int idx = rand() % 4;
        train(net, inputs[idx], targets[idx], lr);
    }
}

void save_network(Network *net){
    (void)net;
}

void load_network(FILE *file){
    (void)file;
}

int main(){

    srand(time(NULL));

    Network net;
    init_network(&net);

    double inputs[4][2] = { {0,0}, {0,1}, {1,0}, {1,1}};

    double targets[NB_SAMPLES][NB_OUTPUTS] = {
        {1.0},
        {0.0},
        {0.0},
        {1.0}
    };

    double lr = 0.5;
    int epochs = 50000;

    complete_train(&net, epochs, lr, inputs, targets);
    show_results(&net, inputs, targets);

    return EXIT_SUCCESS;
}