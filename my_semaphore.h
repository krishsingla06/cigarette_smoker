#ifndef MY_SEMAPHORE_H
#define MY_SEMAPHORE_H
#define MAX_QUEUE 100
#include <pthread.h> 

typedef struct {
    int value;                
    pthread_t queue[MAX_QUEUE];    
    int front, rear;         
} my_semaphore;


void sem_init_custom(my_semaphore *sem, int initial_value);
void sem_wait_custom(my_semaphore *sem, pthread_t pid);
void sem_signal_custom(my_semaphore *sem);

#endif
