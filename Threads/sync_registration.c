#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

const int NSLOTS = 25;
const int FREE = 0;
const int USED = 1;

sem_t freeslots;
sem_t full;
sem_t mutex;

int slotState[NSLOTS];

int registration() {
    int slotNo = -1;

    sem_wait(&freeslots);
    sem_wait(&mutex);
    for(int i = 0; i < NSLOTS ; i++) {
        if(slotState[i] == FREE) {
            slotNo = i;
            slotState[i] = USED;
            break;
        }
    }
    sem_post(&mutex);
    sem_post(&full);
    return slotNo;
}

int cancel() {
    
    int cancelSlot = -1;

    sem_wait(&full);
    sem_wait(&mutex);

    for(int i = 0; i < NSLOTS; i++) {
        if(slotState[i] == USED) {
            cancelSlot = i;
            slotState[i] = FREE;
            break;
        }
    }

    sem_post(&mutex);
    sem_post(&freeslots);

    return cancelSlot;
}

int main() {
   
    for(int i = 0; i < NSLOTS; i++) {
        slotState[i] = FREE;
    }
    slotState[0] = USED;
    slotState[1] = USED;
    slotState[2] = USED;

    sem_init(&freeslots, 0, 25);
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 25);
    
    sem_wait(&freeslots);
    sem_wait(&freeslots);
    sem_wait(&freeslots);

    for (int i = 0; i <NSLOTS-3; i++)
        sem_wait(&full);
    int c;
    int sem_freeslots_value;
    int sem_full_value;
    int sem_mutex_value;

    do {
        sem_getvalue(&freeslots, &sem_freeslots_value);
        sem_getvalue(&full, &sem_full_value);
        printf("\n------------\nAvailable slots = %d | Taken slots = %d\n----------------\n", sem_freeslots_value, sem_full_value);
        printf("Press 1 to register, 2 to cancel, 3 to quit...:");
        scanf("%d", &c);
        if (c == 1) {
            int reg = registration();
            sem_getvalue(&freeslots, &sem_freeslots_value);
            sem_getvalue(&full, &sem_full_value);
            sem_getvalue(&mutex, &sem_mutex_value);
            if (reg >= 0) 
                printf("Register successful!\n");
            else
                printf("Register failed!!!\n");
            printf("Free Slots = %d | Full = %d | Mutex = %d\n", sem_freeslots_value, sem_full_value, sem_mutex_value);
        }
        else if (c == 2) {
            int cal = cancel();
            sem_getvalue(&freeslots, &sem_freeslots_value);
            sem_getvalue(&full, &sem_full_value);
            sem_getvalue(&mutex, &sem_mutex_value);
            if (cal >= 0 ) 
                printf("Cancel successful!\n");
            else
                printf("Cancel failed!!!\n");
            printf("Free Slots = %d | Full = %d | Mutex = %d\n", sem_freeslots_value, sem_full_value, sem_mutex_value);    
        }
        else   
            break;     
    }while(c != 3);

    sem_destroy(&mutex);
    sem_destroy(&freeslots);
    sem_destroy(&full);
    return 0;
}

