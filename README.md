# Banker's Algorithm Implementation

This project implements the Banker's Algorithm for deadlock avoidance in a multithreaded environment. It demonstrates resource allocation and safety checks while preventing race conditions and deadlocks.

## Prerequisites

### For Nix Users
- Nix package manager installed
- Nix flakes enabled

### For Standard C Compilation
- GCC compiler (version 14.2.1 or compatible)
- POSIX threads library (pthread)
- Standard C library

## Running with Nix

1. Enter the Nix development shell:
```bash
nix develop
```

2. Run the program with initial resource counts:
```bash
nix run . -- <resource1> <resource2> <resource3>
```
Example:
```bash
nix run . -- 10 5 7
```

## Running without Nix

1. Compile the program:
```bash
gcc -o banker banker.c -pthread
```

2. Run the compiled program:
```bash
./banker <resource1> <resource2> <resource3>
```
Example:
```bash
./banker 10 5 7
```

## Program Behavior

The program creates 5 customer threads that continuously:
1. Request random resources
2. Use granted resources
3. Release resources
4. Wait before next request

The Banker's Algorithm ensures:
- Safe resource allocation
- Deadlock prevention
- Race condition avoidance
- Proper resource release

## Output Explanation

The program displays:
1. Initial state with available resources and maximum matrix
2. Customer request status (granted/denied)
3. Resource release notifications

Example output:
```
Initial State:
Available resources: 10 5 7 

Maximum matrix:
Customer 0: 1 2 2 
Customer 1: 5 5 1 
Customer 2: 2 5 4 
Customer 3: 2 1 3 
Customer 4: 2 4 4 

Customer 4: Request granted
Customer 3: Request granted
Customer 1: Request granted
...
```

## Implementation Details

The implementation includes:
- Mutex locks for thread synchronization
- Safety algorithm for deadlock prevention
- Resource request/release mechanisms
- Random resource request generation
- Proper error handling

## Notes

- The program runs indefinitely until interrupted (Ctrl+C)
- Resource requests are bounded by customer needs
- System maintains safety through the Banker's Algorithm
- All resource allocations are tracked and verified 