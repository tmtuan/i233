/*
 * I233E -- Lecture 3: Threads
 *
 * Demo on thread creation using the pthread library.
 */

#include <stdio.h>
#include <pthread.h>

struct timespec quarter_sec = {0, 250000000};
struct timespec tenth_sec   = {0, 100000000};

void *child_thread(void* arg)
{
  printf("\t\t Child: I am the child thread.\n");
  int i;
  for (i = 0; i < 26; i++) {
    printf("\t\t Child: %d\n", i);
    nanosleep(&quarter_sec, NULL);
  }
  printf("\t\t Child: Thread finished.\n");
  pthread_exit(0);
}

int main(int argc, char *argv[])
{
  pthread_t thr_id;

  pthread_create(&thr_id, NULL, &child_thread, NULL);

  /* Main thread */
  int i;
  for (i = 0; i < 26; i++) {
    printf("Parent: %c\n", i + 'A');
    nanosleep(&tenth_sec, NULL);
  }
  printf("Parent: Waiting for the child to finish...\n");
  pthread_join(thr_id, NULL);
  printf("Parent: Child thread has finished.\n");
  return 0;
}