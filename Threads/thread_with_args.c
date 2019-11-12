#include <stdio.h>
#include <pthread.h>

void *child_thread(void* arg) {
    
    printf("Child thread.\n");
    pthread_exit(0);
}

int main() {
    
    pthread_t thr_id;

    printf("Main thread.\n");

    pthread_create(&thr_id, NULL, &child_thread, NULL);

    pthread_join(thr_id, NULL);
    
    return 0;
}