#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000000000

#define STATIC

int main() {

#ifdef STATIC
    double array[SIZE];
#else
    double *array;

    array = (double *)malloc(SIZE * sizeof(double));
    if (array == NULL) {
        printf("ERROR: Memory allocation failed!!!");
        return 1;
    }
#endif

    double sum = 0.0;

    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
        sum += array[i];
    }
    printf("Result = %f\n", sum);

#ifndef STATIC
    free(array);
#endif
    return 0;
}