#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Mutexes representing two resources
pthread_mutex_t resource1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource2 = PTHREAD_MUTEX_INITIALIZER;

// Function preventing deadlock
void *deadlock_prevented(void *arg) {
    int thread_id = *(int *)arg;

    // Both threads acquire locks in the same order (resource1 -> resource2)
    pthread_mutex_lock(&resource1);
    printf("Thread %d: Locked Resource 1\n", thread_id);

    sleep(1); // Simulate processing

    pthread_mutex_lock(&resource2);
    printf("Thread %d: Locked Resource 2\n", thread_id);

    pthread_mutex_unlock(&resource2);
    pthread_mutex_unlock(&resource1);

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    printf("\n*** Preventing Deadlock with Ordered Locks ***\n");
    pthread_create(&t1, NULL, deadlock_prevented, &id1);
    pthread_create(&t2, NULL, deadlock_prevented, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    // print join the threads and print the final message
    printf("Threads have completed successfully!\n");
    
    return 0;
}
