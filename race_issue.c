#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define NUM_INCREMENTS 1000000

int counter = 0; // Shared variable

void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        counter++; // Critical section
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }
    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    // Print final counter value
    printf("Final Counter Value: %d\n", counter); // Expected: NUM_THREADS * NUM_INCREMENTS
    return 0;
}
