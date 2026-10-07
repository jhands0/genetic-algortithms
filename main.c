#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));
    FILE *out_file = fopen("fitness_values.txt", "w");
    fprintf(out_file, "AVERAGE\tBEST\n");
}