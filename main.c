#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GENE_COUNT  3
#define LOW        -5.
#define HIGH        5.

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

typedef struct {
    double genes[GENE_COUNT];
    double fitness;
    double (*calc_function)(Chromosome *);
    double (*calc_fitness)(Chromosome *);
    double (*print)(Chromosome *);
} Chromosome;

double calculate_function(Chromosome *self) {
    double value = 100. * pow((self->genes[1] - pow(self->genes[0], 2.)),2.) + pow((1. - self->genes[0]), 2.)
                 + 100. * pow((self->genes[2] - pow(self->genes[1], 2.)),2.) + pow((1. - self->genes[1]), 2.);
    return value;
}

double calculate_fitness(Chromosome *self) {
    double value = self->calc_function(self);
    return 1. / (1. + fabs(value));
}

void printf_chromosome(Chromosome *self) {
    printf("%lf : %lf, %lf, %lf\n", self->fitness, self->genes[0], self->genes[1], self->genes[2]);
}

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));
    FILE *out_file = fopen("fitness_values.txt", "w");
    fprintf(out_file, "AVERAGE\tBEST\n");
}