#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//#define GENE_COUNT 3;

int random_int(int low, int high) {
    int diff = high - low
    return (rand() % diff) - low;
}

double random_double(double low, double high) {
    return ((double) rand() / (double) RAND_MAX) * (high - low) + low;
}

double normal_distribution() {
    double y1 = random_double(0., 1.);
    double y2 = random_double(0., 1.);
    return cos(2. * 3.14 * y2) * sqrt(-2. * log(y1));
}

//typedef struct {
//    double genes[GENE_COUNT];
//    double fitness;
//} Chromosome;

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));
    FILE *out_file = fopen("fitness_values.txt", "w");
    fprintf(out_file, "AVERAGE\tBEST\n");
}