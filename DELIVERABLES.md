# Lab Assignment: Multithreaded Banker's Algorithm Implementation

For this lab, you will write a multithreaded program that implements **Banker's Algorithm** discussed in class ([document attached]). Multiple customers will request/release resources from/to _the bank_. Requests will only be granted if they leave system safe state - unsafe requests denied.


## Core Requirements  
This program combines three key concepts:  
```c
/* these may be any values >=0 */
#define NUMBER_OF_CUSTOMERS5 
#define NUMBER_OF_RESOURCES3 
/* available amountofeach resource */
int available[NUMBER_OF_RESOURCES];
/* maximum demandofeach customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* currently allocated resources */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* remaining needs */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
```

### Customer Threads  
Create `n` threads performing continuous loop:
- Request random resources bounded by `need[]`
- Release random resources  

Use mutex locks (`Pthreads`) for shared data access control.


### Key Functions  
```c 
// Returns0ifgranted,-ifdenied 
int request_resources(intcustomer_num,intrequest[]);  
```
```c 
// Returns0ifsuccessful,-iferror 
int release_resources(intcustomer_num,intrelease[]);   
```

### Execution & Initialization  
Run programwith resource countsasCLIarguments(e.g.):  

```bash ./a.out1057 ```

Initialize arrays:
- `available`: From CLI arguments  
- `maximum`: Custom initialization method permitted


> **Critical Constraints**: Must prevent race conditions through mutex lockingand implement full safety algorithm checks.