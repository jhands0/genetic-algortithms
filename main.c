#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define GENE_COUNT          3
#define POPULATION_SIZE     100
#define GENERATIONS         750
#define TOURNAMENT_SIZE     10
#define CROSSOVER_CHANCE    0.7
#define MUTATION_CHANCE     0.3
#define LOW                 -5.
#define HIGH                5.

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
    printf("%lf : %lf, %lf, %lf\n", chromosome.fitness, chromosome.genes[0], chromosome.genes[1], chromosome.genes[2]);
}

Chromosome *generate_population() {
    Chromosome *chromosomes = (Chromosome*) calloc(POPULATION_SIZE, sizeof(Chromosome));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int g = 0; g < GENE_COUNT; g++) {
            chromosomes[i].genes[g] = random_double(LOW, HIGH);
        }
        chromosomes[i].fitness = calculate_fitness(chromosomes[i]);
    }
    return chromosomes;
}

Chromosome get_average_fitness(Chromosome *population) {
    double average = 0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        average = average + population[i].fitness;
    }
    return average / POPULATION_SIZE;
}

Chromosome get_best_chromosome(Chromosome *population, int size) {
    double max_fitness = 0.0;
    int winner_index = 0;
    for (int c = 0; c < size; c++) {
        if (population[c].fitness > max_fitness) {
            max_fitness = population[c].fitness;
            winner_index = c;
        }
    }
    return population[winner_index];
}

Chromosome *tournament_selection(Chromosome *population) {
    Chromosome *new_population = (Chromosome*) calloc(POPULATION_SIZE, sizeof(Chromosome));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        Chromosome tournament_chromosomes[TOURNAMENT_SIZE];
        for (int t = 0; t < TOURNAMENT_SIZE; t++) {
            int index = random_int(0, POPULATION_SIZE);
            tournament_chromosomes[t] = population[index];
        }
        new_population[i] = get_best_chromosome(tournament_chromosomes, TOURNAMENT_SIZE);
    }
    return new_population;
}

Chromosome *uniform_crossover(Chromosome *population) {
    Chromosome *new_population = (Chromosome*) calloc(POPULATION_SIZE, sizeof(Chromosome));
    for (int i = 0; i < POPULATION_SIZE / 2; i++) {
        Chromosome chr_1 = population[random_int(0, POPULATION_SIZE)];
        Chromosome chr_2 = population[random_int(0, POPULATION_SIZE)];
        if (random_double(0., 1.) < CROSSOVER_CHANCE) {
            double genes_1[GENE_COUNT];
            double genes_2[GENE_COUNT];
            for (int g = 0; g < GENE_COUNT; g++) {
                if (random_double(0., 1.) < 0.5) {
                    genes_1[g] = chr_1.genes[g];
                } else {
                    genes_1[g] = chr_2.genes[g];
                }
                if (random_double(0., 1.) < 0.5) {
                    genes_2[g] = chr_1.genes[g];
                } else {
                    genes_2[g] = chr_2.genes[g];
                }
            }
            Chromosome new_chr_1, new_chr_2;
            for (int g = 0; g < GENE_COUNT; g++) {
                new_chr_1.genes[g] = genes_1[g];
                new_chr_2.genes[g] = genes_2[g];
            }
            new_chr_1.fitness = calculate_fitness(new_chr_1);
            new_chr_2.fitness = calculate_fitness(new_chr_2);
            new_population[i] = new_chr_1;
            new_population[POPULATION_SIZE - 1 - i] = new_chr_2;
        } else {
            new_population[i] = chr_1;
            new_population[POPULATION_SIZE - 1 - i] = chr_2;
        }
    }
    return new_population;
}

Chromosome *gaussian_mutation(Chromosome *population) {
    Chromosome *new_population = (Chromosome*) calloc(POPULATION_SIZE, sizeof(Chromosome));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        double new_genes[GENE_COUNT];
        for (int g = 0; g < GENE_COUNT; g++) {
            double old_gene = population[i].genes[g];
            if (random_double(0., 1.) < MUTATION_CHANCE) {
                new_genes[g] = old_gene + normal_distribution() * 0.1 * (HIGH - LOW);
            } else {
                new_genes[g] = old_gene;
            }
        }
        Chromosome new_chromosome;
        for (int g = 0; g < GENE_COUNT; g++) {
            new_chromosome.genes[g] = new_genes[g];
        }
        new_chromosome.fitness = calculate_fitness(new_chromosome);
        new_population[i] = new_chromosome;
    }
    return new_population;
}

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));
    FILE *out_file = fopen("fitness_values.txt", "w");
    fprintf(out_file, "AVERAGE\tBEST\n");

    Chromosome *population = generate_population();

    
}