#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GENE_COUNT      3
#define POPULATION_SIZE 100
#define LOW            -5.
#define HIGH            5.

int random_int(int low, int high) {
    int diff = high - low;
    return (rand() % diff) + low;
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
    int id;
    double genes[GENE_COUNT];
    double fitness;
} Chromosome;

double calculate_function(Chromosome chromosome) {
    double value = 100. * pow((chromosome.genes[1] - pow(chromosome.genes[0], 2.)),2.) + pow((1. - chromosome.genes[0]), 2.)
                 + 100. * pow((chromosome.genes[2] - pow(chromosome.genes[1], 2.)),2.) + pow((1. - chromosome.genes[1]), 2.);
    return value;
}

double calculate_fitness(Chromosome chromosome) {
    double value = calculate_function(chromosome);
    return 1. / (1. + fabs(value));
}

void printf_chromosome(Chromosome chromosome) {
    printf("%d: %lf : %lf, %lf, %lf\n", chromosome.id, chromosome.fitness, chromosome.genes[0], chromosome.genes[1], chromosome.genes[2]);
}

Chromosome *generate_population() {
    Chromosome *chromosomes = (Chromosome*) calloc(POPULATION_SIZE, sizeof(Chromosome));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < GENE_COUNT; j++) {
            chromosomes[i].genes[j] = random_double(LOW, HIGH);
        }
        chromosomes[i].id = i;
        chromosomes[i].fitness = calculate_fitness(chromosomes[i]);
        printf_chromosome(chromosomes[i]);
    }
    return chromosomes;
}

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));
    FILE *out_file = fopen("fitness_values.txt", "w");
    fprintf(out_file, "AVERAGE\tBEST\n");

    Chromosome *population = generate_population();
}