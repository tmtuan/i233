/*
* I233E - Assignment 2 - Problem 2
* Student's Name: TRAN Minh Tuan
* Student's ID: 1920428
*/
#include <pthread.h>
#include <stdio.h>

// Global variables
const long NUM = 5;
long SUM = 0; // SUM to be calculated by child threads
long val = 0; // value created by a child thread
pthread_mutex_t lock; // mutex for synchronous calculation of SUM

void *child_thread(void * arg);

int main() {

    pthread_t threads[NUM];
    int check_t = 0;
    printf("Main thread: Starting creating %ld threads...\n", NUM);
    for(long i = 0; i < NUM; i++) {
        printf("--> Creating thread %ld...\n", i);
        if(pthread_create(&threads[i], NULL, &child_thread, NULL) != 0) {
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
        printf("Main thread: Created %ld threads.\n", NUM);
    }
    printf("Main thread: Calculated SUM = %ld\n", SUM);
    printf("Main thread: Expected   SUM = %ld\n", NUM*(NUM+1)/2);
    return 0;
}

void *child_thread(void * arg) {
    
    if(pthread_mutex_lock(&lock) != 0) {
        fprintf(stderr, "Failed to lock mutex");
    }
    else {
        val = val + 1;
        printf("\n------ Child thread: Value assigned to child thread = %ld\n", val);
        SUM += val;
        if(pthread_mutex_unlock(&lock) != 0) {
            fprintf(stderr, "Failed to unlock mutex");
        }
    }

    pthread_exit(0);
}