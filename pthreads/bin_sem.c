
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 1

static sem_t fuel_sem;
static int *fuel;

void *func(void *arg) {
    // sleep(1);
    // sem_wait(&fuel_sem);
    *fuel += 50;
    printf("Current value of fuel: %d\n", *fuel);
    sem_post(&fuel_sem);
}


int main(void) {
    // initialize semaphore
    sem_init(&fuel_sem, 0, 0);
    pthread_t th[NUM_THREADS];
    fuel = (int*)malloc(sizeof(int));
    *fuel = 50;

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&th[i], NULL, &func, NULL) != 0) {
            perror("Unable to create thread");
        }
    }
    sem_wait(&fuel_sem);

    printf("Fuel: %d\n", *fuel);
    printf("Deallocating fuel\n");
    free(fuel);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Thread unable to join");
        }
    }
    // destroy semaphore
    sem_destroy(&fuel_sem);
}