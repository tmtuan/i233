/*
* I233E - Assignment 2 - Problem 2
* Student's Name: TRAN Minh Tuan
* Student's ID: 1920428
*/
#include <pthread.h>
#include <stdio.h>

#define NUM 5
typedef struct {
    int val;
}thread_arg;

long SUM = 0;
long numbers[NUM] = {1,2,3,4,5};

void *child_thread(void * arg);

int main() {

    pthread_t threads[NUM];
    int check_t = 0;
    printf("Starting creating %d threads...\n", NUM);
    for(int i = 0; i < NUM; i++) {
        printf("Creating thread %d...\n", i);
        if(pthread_create(&threads[i], NULL, &child_thread, (void *) numbers[i]) != 0) {
            perror("Failed to create threads!!!");
            return 1;
        }
        else {
            check_t++;
        }
    }

    for(int i = 0; i < NUM; i++) {
        if(pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join threads!!!");
            return 1;
        }
    }

    if(check_t == NUM) {
        printf("Created %d threads.\n", NUM);
    }
    printf("Calculated SUM = %ld\n", SUM);
    printf("Expected   SUM = 15\n");
    return 0;
}

void *child_thread(void * arg) {
    
    long n;
    n = (long)arg;

    printf("Number assigned to this thread = %ld\n", n);
    SUM += n;
    
    pthread_exit(0);

}