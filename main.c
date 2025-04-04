#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "my_semaphore.h"

int r1 = 0, r2 = 0, r3 = 0; 

my_semaphore tobacco, paper, match;
my_semaphore next_round;

void* agent(void* arg) {
    printf("Agent: Starting...\n");

    while (1) {
        pthread_t tid = pthread_self();
        sem_wait_custom(&next_round, tid); 
        int item1 = rand() % 3;
        int item2 = ((rand() % 2) + item1 + 1) % 3;

        printf("Agent: Producing items %d and %d\n", item1, item2);

        if (item1 == 0) {
            sem_signal_custom(&tobacco);
        } else if (item1 == 1) {
            sem_signal_custom(&paper);
        } else {
            sem_signal_custom(&match); 
        }

        if (item2 == 0) {
            sem_signal_custom(&tobacco); 
        } else if (item2 == 1) {
            sem_signal_custom(&paper);
        } else {
            sem_signal_custom(&match);
        }
    }
}

void* f1(void* arg) {
    while (1) {
        pthread_t tid = pthread_self(); 
        sem_wait_custom(&tobacco, tid); 
        //printf("f1: tobacco acquired\n");
        r2++; r3++;
    }
}

void* f2(void* arg) {
    while (1) {
      pthread_t tid = pthread_self();
       sem_wait_custom(&paper, tid); 
       // printf("f2: paper acquired\n");
        r1++; r3++;
    }
}

void* f3(void* arg) {
    while (1) {
        pthread_t tid = pthread_self();
        sem_wait_custom(&match, tid);
       // printf("f3: match acquired\n");
        r1++; r2++;
    }
}

void* smoker(void* arg) {
    int id = *(int*)arg; 

    printf("Smoker %d: Starting...\n", id);

    while (1) {
        if (id == 0) {
            while (r1 != 2);
        } else if (id == 1) {
            while (r2 != 2);
        } else {
            while (r3 != 2);
        }

        printf("Smoker %d: Smoking...\n", id);
        sleep(1);
        r1 = 0; r2 = 0; r3 = 0;
        sem_signal_custom(&next_round); 
    }
}

int main() {
    r1 = 0; r2 = 0; r3 = 0;
    sem_init_custom(&tobacco, 0); 
    sem_init_custom(&paper, 0);
    sem_init_custom(&match,  0);
    sem_init_custom(&next_round, 1);

    pthread_t agent_thread, f_threads[3], smoker_threads[3];
    int smoker_ids[3] = {0, 1, 2};

    pthread_create(&f_threads[0], NULL, f1, NULL); 
    pthread_create(&f_threads[1], NULL, f2, NULL);
    pthread_create(&f_threads[2], NULL, f3, NULL);

    printf("fthreads created\n");
    sleep(1);

    pthread_create(&smoker_threads[0], NULL, smoker, &smoker_ids[0]);
    pthread_create(&smoker_threads[1], NULL, smoker, &smoker_ids[1]);
    pthread_create(&smoker_threads[2], NULL, smoker, &smoker_ids[2]);

    printf("smoker threads created\n");

    sleep(1);

    pthread_create(&agent_thread, NULL, agent, NULL);

    sleep(1);

    for (int i = 0; i < 3; i++) {
        pthread_join(f_threads[i], NULL); 
    }
    printf("f threads joined\n");
    for (int i = 0; i < 3; i++) {
        pthread_join(smoker_threads[i], NULL); 
    }
    printf("smoker threads joined\n");
    pthread_join(agent_thread, NULL); 
    printf("agent thread joined\n");

    return 0; 
}