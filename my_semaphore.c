#include <stdio.h>
#include "my_semaphore.h"

void sem_init_custom(my_semaphore *sem, int initial_value) {
    sem->value = initial_value;
    sem->front = 0;
    sem->rear = 0;
}

// void enqueue(my_semaphore *sem, pthread_t tid) {
//     if ((sem->rear + 1) % MAX_QUEUE == sem->front) {
//         printf("Queue is full!\n");
//         return;
//     }
//     sem->queue[sem->rear] = tid;
//     sem->rear = (sem->rear + 1) % MAX_QUEUE;
// }

// pthread_t dequeue(my_semaphore *sem) {
//     if (sem->front == sem->rear) {
//         pthread_t dummy_tid = {0};
//         return dummy_tid;
//     }
//     pthread_t tid = sem->queue[sem->front];
//     sem->front = (sem->front + 1) % MAX_QUEUE;
//     return tid;
// }

void sem_wait_custom(my_semaphore *sem, pthread_t tid) {
    sem->value--;
    while(sem->value < 0);
    // if (sem->value < 0) {
    //     //printf("Process %d is waiting...\n", tid);
    //     // enqueue(sem, tid);
        
    //     // dequeue(sem); 
    //    // sem->value++; 
    // } else {
    //    // printf("Process %d entered critical section\n", tid);
    // }
}

void sem_signal_custom(my_semaphore *sem) {
    sem->value++;
}

