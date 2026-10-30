#include "../include/neural_network/neural_network.h"
#include "../include/neural_network/emnlist_loader.h"

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

// need to update the training for the letters
void complete_train(Network *net, int epochs, double lr, double **inputs, double **targets) {

    for (int step = 0; step < epochs; step++) {
        int idx = rand() % 4; //fix
        train(net, inputs[idx], targets[idx], lr);

        // printf("Epoch %d / %d\n", step + 1, epochs);
    }
    // printf("\n\n");
}

void test_results(Network *net, int nb_samples, double **inputs, double **targets) {
    printf("--- Results ---\n");
    for (int i = 0; i < nb_samples; i++) {
        forward(net, inputs[i]);
        
        printf("Sample %d -> Inputs: [", i);
        for (int j = 0; j < NB_INPUTS; j++) {
            printf("%.0f%s", inputs[i][j], (j < NB_INPUTS - 1) ? ", " : "");
        }
        printf("] | ");

        for (int k = 0; k < NB_OUTPUTS; k++) {
            printf("Expected: %.0f | Pred: %.4f (Bit: %d) ",
                   targets[i][k], net->output[k], net->output[k] >= 0.5 ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n\n");
}

void show_wb(Network *net){
    printf("--- Weight & biases ---\n");

    for (int i = 0; i < NB_HIDDEN; i++) {
        for (int j = 0; j < NB_INPUTS; j++) {
            printf("Hidden weight of node  [%d, %d] : %f\n", i, j, net->w_hidden[i][j]);
        }
    }
    for (int j = 0; j < NB_HIDDEN; j++) {
        printf("Hidden bias of node  [%d] : %f\n", j, net->b_hidden[j]);
    }
    for (int i = 0; i < NB_OUTPUTS; i++) {
        for (int j = 0; j < NB_HIDDEN; j++) {
            printf("Output weight of node [%d, %d] : %f\n", i, j, net->w_output[i][j]);
        }
        printf("Output bias of node [%d] : %f\n", i, net->b_output[i]);
    }
    printf("\n\n");
}

int save_network(Network *net, char *path){
    FILE *file = fopen(path, "w");
    if (file == NULL) return 0;

    fwrite(net->w_hidden, sizeof(double), NB_HIDDEN * NB_INPUTS, file);
    fwrite(net->b_hidden, sizeof(double), NB_HIDDEN, file);

    fwrite(net->w_output, sizeof(double), NB_OUTPUTS * NB_HIDDEN, file);
    fwrite(net->b_output, sizeof(double), NB_OUTPUTS, file);

    fclose(file);

    printf("Saved in %s\n", path);
    return 1;
}

Network *load_network(char *path){
    FILE *file = fopen(path, "rb");
    if (!file) return NULL;

    Network *net = malloc(sizeof(Network));
    
    fread(net->w_hidden, sizeof(double), NB_HIDDEN * NB_INPUTS, file);
    fread(net->b_hidden, sizeof(double), NB_HIDDEN, file);
    
    fread(net->w_output, sizeof(double), NB_OUTPUTS * NB_HIDDEN, file);
    fread(net->b_output, sizeof(double), NB_OUTPUTS, file);

    fclose(file);

    return net;
}

int predict_xnor(Network *net, double input[NB_INPUTS]) {
    forward(net, input);
    int result = net->output[0] >= 0.5 ? 1 : 0; 
    printf("XNOR(%0.f, %0.f) = %d\n", input[0], input[1], result);
    return result;
}

char predict_char(Network *net, double *input){

    forward(net, input);

    int best_index = 0;
    double max_output = net->output[0];

    for (int i = 1; i < NB_OUTPUTS; i++) {
        if (net->output[i] > max_output) {
            max_output = net->output[i];
            best_index = i;
        }
    }

    return (char)('A' + best_index);
}

char get_expected_char(Dataset *dataset, int sample_index) {
    if (!dataset || sample_index < 0 || sample_index >= dataset->count) {
        return '?';
    }

    for (int k = 0; k < NB_OUTPUTS; k++) {
        if (dataset->targets[sample_index][k] > 0.5) {
            return (char)('A' + k);
        }
    }

    return '?';
}

int main(){

    srand(time(NULL));

    Network *net = malloc(sizeof(Network));
    init_network(net);

    double xnor_raw[4][2] = { {0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0} };
    double targets_raw[4][1] = { {1.0}, {0.0}, {0.0}, {1.0} };
    double *xnor_inputs[4] = { xnor_raw[0], xnor_raw[1], xnor_raw[2], xnor_raw[3] };
    double *xnor_targets[4] = { targets_raw[0], targets_raw[1], targets_raw[2], targets_raw[3] };

    double lr = 0.5;
    int epochs = 50000;

    complete_train(net, epochs, lr, xnor_inputs, xnor_targets);
    show_wb(net);
    save_network(net, "include/saved_networks/net1");

    printf("Loaded model :\n");
    Network *savedNet = load_network("include/saved_networks/net1");
    if (savedNet){
        test_results(savedNet, 4, xnor_inputs, xnor_targets);

        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 2; j++)
            {
                double sample[2] = {i, j};
                predict_xnor(savedNet, sample);
            }
        }
        
    }

    // for letters
    // training does not work as expected for now, fix train_complete

    // Dataset *dataset = load_emnist_dataset(
    //     "tests/emnist-letters-train-images-idx3-ubyte",
    //     "tests/emnist-letters-train-labels-idx1-ubyte",
    //     100000
    // );

    // complete_train(net, 30, 0.05, dataset->inputs, dataset->targets);
    // save_network(net, "include/saved_networks/net_letters");
    // Network *saved = load_network("include/saved_networks/net_letters");

    // for(int i = 0; i < 42; i++){
    //     char e = get_expected_char(dataset, i);
    //     char p = predict_char(saved, dataset->inputs[i]);
    //     printf("Expected letter : %c | Predicted letter : %c\n", e, p);
    // }
    
    // free_dataset(dataset);
    free(net);

    return EXIT_SUCCESS;
}