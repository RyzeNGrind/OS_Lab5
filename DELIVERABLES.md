# Lab Assignment: Multithreaded Banker's Algorithm Implementation  

## Overview  
For this lab, you will write a multithreaded program that implements the banker’s algorithm discussed in class (document attached). Customers request/release resources from the bank. The banker grants requests **only** if they leave the system in a safe state; unsafe requests are denied. This assignment combines three topics:  
1. Multithreading  
2. Preventing race conditions  
3. Deadlock avoidance  

---

## The Banker  
The banker manages `n` customers competing for `m` resource types using these data structures:  

```c
/* Values may be >= 0 */
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

/* Available amount of each resource */
int available[NUMBER_OF_RESOURCES];

/* Maximum demand of each customer */ 
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* Amount currently allocated */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

/* Remaining need */ 
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
```

---

## The Customers  
Create `n` customer threads that continually loop between requesting/releasing **random** resources bounded by their `need[]`. Use mutex locks for shared data access (`request_resources()`/`release_resources()`):  

### Function Prototypes  
```c
// Returns 0 if successful (granted), -1 otherwise 
int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);
```

---

## Implementation Details  
### Program Invocation Example:
Initialize resource counts via command line arguments:
```bash
./a.out 10 5 7    # Available = [10 ,5 ,7]
```

### Core Algorithms  
Bankers rely on two algorithms:
1.**Safety Algorithm** — Checks system safety under current state.
2.**Resource-Request Algorithm** — Validates safe granting of requests.


### Requirements Summary   
Write a multithreaded C program where:
- Processes request/release resources dynamically.
- Requests require safety validation via bankers algorithm.
- Mutex locks prevent race conditions during shared data access.