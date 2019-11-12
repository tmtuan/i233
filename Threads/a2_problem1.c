/*
* I233E - Assignment 2 - Problem 1
* Student's Name: TRAN Minh Tuan
* Student's ID: 1920428
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// Number of child threads
int N_THREADS = 5;

const char *messages[] = {
    "Mina-san kon'nichiwa!",
    "Hello everyone!",
    "Bonjour tout le monde!",
    "Ni men hao!",
    "Chao moi nguoi!"
};

void *child_thread(void *arg);

int main() {

    pthread_t threads[N_THREADS];

    // Main thread is creating child threads....
    for(int i = 0; i < N_THREADS; i++) {
        if(pthread_create(&threads[i], NULL, &child_thread, (void *) messages[i]) != 0) {
            perror("pthread_create: Failed to create child threads");
            return 1;
        }
    }

    for(int i = 0; i < N_THREADS; i++) {
        if(pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join: Failed to join theads");
            return 1;
        }
    }
    return 0;
}

void *child_thread(void *arg) {

    char *message = (char *)arg;  
    printf("\t%s\n", message);
    pthread_exit(0);
}