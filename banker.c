#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

// Global data structures
int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

// Mutex for protecting shared resources
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to check if a state is safe
bool is_safe_state() {
    int work[NUMBER_OF_RESOURCES];
    bool finish[NUMBER_OF_CUSTOMERS];
    
    // Initialize work and finish arrays
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        finish[i] = false;
    }
    
    // Find a safe sequence
    while (true) {
        bool found = false;
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    // Process can complete
                    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
        
        if (!found) break;
    }
    
    // Check if all processes finished
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (!finish[i]) return false;
    }
    return true;
}

// Function to request resources
int request_resources(int customer_num, int request[]) {
    pthread_mutex_lock(&mutex);
    
    // Check if request exceeds need
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (request[i] > need[customer_num][i]) {
            pthread_mutex_unlock(&mutex);
            return -1;
        }
    }
    
    // Check if request exceeds available
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (request[i] > available[i]) {
            pthread_mutex_unlock(&mutex);
            return -1;
        }
    }
    
    // Try to allocate resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }
    
    // Check if state is safe
    if (!is_safe_state()) {
        // Restore previous state
        for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
            available[i] += request[i];
            allocation[customer_num][i] -= request[i];
            need[customer_num][i] += request[i];
        }
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    
    pthread_mutex_unlock(&mutex);
    return 0;
}

// Function to release resources
int release_resources(int customer_num, int release[]) {
    pthread_mutex_lock(&mutex);
    
    // Check if release exceeds allocation
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (release[i] > allocation[customer_num][i]) {
            pthread_mutex_unlock(&mutex);
            return -1;
        }
    }
    
    // Release resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];
    }
    
    pthread_mutex_unlock(&mutex);
    return 0;
}

// Customer thread function
void* customer(void* arg) {
    int customer_num = *(int*)arg;
    int request[NUMBER_OF_RESOURCES];
    
    while (true) {
        // Generate random request (smaller requests to increase chances of success)
        for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
            if (need[customer_num][i] > 0) {
                request[i] = rand() % (need[customer_num][i] + 1);
            } else {
                request[i] = 0;
            }
        }
        
        // Request resources
        if (request_resources(customer_num, request) == 0) {
            printf("Customer %d: Request granted\n", customer_num);
            sleep(rand() % 3 + 1); // Simulate work
            
            // Release resources
            if (release_resources(customer_num, request) == 0) {
                printf("Customer %d: Resources released\n", customer_num);
            }
        } else {
            printf("Customer %d: Request denied\n", customer_num);
        }
        
        sleep(rand() % 2 + 1); // Wait before next request
    }
    
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != NUMBER_OF_RESOURCES + 1) {
        printf("Usage: %s <resource1> <resource2> <resource3>\n", argv[0]);
        return 1;
    }
    
    // Initialize random seed
    srand(time(NULL));
    
    // Initialize available resources
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] = atoi(argv[i + 1]);
    }
    
    // Initialize maximum, allocation, and need matrices
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            // Generate smaller maximum values to increase chances of successful allocation
            maximum[i][j] = rand() % 5 + 1;
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
    }
    
    // Print initial state
    printf("\nInitial State:\n");
    printf("Available resources: ");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n\nMaximum matrix:\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        printf("Customer %d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Create customer threads
    pthread_t threads[NUMBER_OF_CUSTOMERS];
    int customer_ids[NUMBER_OF_CUSTOMERS];
    
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        customer_ids[i] = i;
        pthread_create(&threads[i], NULL, customer, &customer_ids[i]);
    }
    
    // Wait for threads (they run indefinitely)
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
} 