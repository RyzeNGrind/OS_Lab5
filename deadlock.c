#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Mutexes representing two resources
pthread_mutex_t resource1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource2 = PTHREAD_MUTEX_INITIALIZER;

// Function causing deadlock
void *deadlock_example(void *arg) {
    int thread_id = *(int *)arg;

    if (thread_id == 1) {
        pthread_mutex_lock(&resource1);
        printf("Thread 1: Locked Resource 1\n");

        sleep(1); // Simulate processing

        printf("Thread 1: Waiting for Resource 2...\n");
        pthread_mutex_lock(&resource2); // Deadlock occurs here
        printf("Thread 1: Locked Resource 2\n");

        pthread_mutex_unlock(&resource2);
        pthread_mutex_unlock(&resource1);
    } else {
        pthread_mutex_lock(&resource2);
        printf("Thread 2: Locked Resource 2\n");

        sleep(1); // Simulate processing

        printf("Thread 2: Waiting for Resource 1...\n");
        pthread_mutex_lock(&resource1); // Deadlock occurs here
        printf("Thread 2: Locked Resource 1\n");

        pthread_mutex_unlock(&resource1);
        pthread_mutex_unlock(&resource2);
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    printf("\n*** Demonstrating Deadlock Condition ***\n");
    pthread_create(&t1, NULL, deadlock_example, &id1);
    pthread_create(&t2, NULL, deadlock_example, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // print join the threads and print the final message
    printf("Threads have completed successfully!\n");
    
    return 0;
}
