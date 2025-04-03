#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 2
#define NUM_INCREMENTS 1000000

int counter = 0; // Shared variable
pthread_mutex_t lock; // Mutex lock
void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&lock); // Lock before modifying shared data
        counter++; // Critical section
        pthread_mutex_unlock(&lock); // Unlock after modification
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }
    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    // Destroy the mutex
    pthread_mutex_destroy(&lock);
    // Print final counter value
    printf("Final Counter Value: %d\n", counter); // Expected: NUM_THREADS * NUM_INCREMENTS
    return 0;
}
