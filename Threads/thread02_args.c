#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum;
typedef struct {
    int lower;
    int upper;
}thread_arg;

void *runner(void *param);

int main(int argc, char *argv[]) {

    pthread_t tid;
    pthread_attr_t attr;
    thread_arg *targ = (thread_arg *)malloc(sizeof(thread_arg));

    if ( argc != 3 ) {
        fprintf(stderr, "usage: thread02 <integer value 1> <integer value 2>\n(value 1 < value 2)");
        return -1;
    }
    if ( atoi(argv[1]) > atoi(argv[2]) ) {
        fprintf(stderr, "value 1 must be less than value 2\n");
        return -1;
    }
    targ->lower = atoi(argv[1]);
    targ->upper = atoi(argv[2]);

    // prepare attributes for the thread to be
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, (void *) targ);

    /* waiting for the thread to complete */
    pthread_join(tid, NULL);
    printf("Sum = %d\n", sum);

    free(targ);
    return 0;
}

void *runner(void *param) {
    
    thread_arg *tparam = (thread_arg *)param;
    int lower = tparam->lower;
    int upper = tparam->upper;
    sum = 0;

    for (int i = lower; i <=upper; i++)
        sum += i;

pthread_exit(0);
}