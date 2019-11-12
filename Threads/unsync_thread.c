
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread properties.
long N_THREADS    = 10;
long N_ITERATIONS = 10000;

struct timespec quarter_sec    = {0, 250000000};
struct timespec tenth_sec      = {0, 100000000};
struct timespec thousandth_sec = {0, 001000000};

// Global variable for sum.
long sum = 0;


// Thread body.
void *child_thread(void *arg) {
  
  for (long i=0; i<N_ITERATIONS; i++) {
    sum = sum + 1; // sum++; ++sum;
    nanosleep(&thousandth_sec, NULL);
  }
  
  long *retPTR = new long;
  retPTR[0] = 3;
  return retPTR;
}

// Main function.
int main() {
  pthread_t threads[N_THREADS];
  void * retPtr;
  
  // Make the threads.
  for (long i=0; i<N_THREADS; i++) {
    if (pthread_create(&threads[i], NULL, &child_thread, NULL) != 0) perror("pthread_create");
  }
  getchar();
  
  // Join threads.
  for (long i=0; i<N_THREADS; i++) {
    if (pthread_join(threads[i], &retPtr) != 0) perror("pthread_join");
  }
  
  printf("Threads return = %ld\n\n", *(long *)retPtr);
  delete (long *)retPtr;
  printf("RESULTS:\n");
  printf("\t Computed sum   = %ld\n", sum);
  printf("\t Expected sum   = %ld\n", N_THREADS * N_ITERATIONS);
  
  
  return 0;
}