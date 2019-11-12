#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000000000

int main() {

    //double array[SIZE];
    double *array;

    array = (double *)malloc(SIZE * sizeof(double));
    if (array == NULL) {
        printf("ERROR: Memory allocation failed!!!");
        return 1;
    }
    double sum = 0.0;

    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
        sum += array[i];
    }
    printf("Result = %f\n", sum);

    free(array);

    return 0;
}