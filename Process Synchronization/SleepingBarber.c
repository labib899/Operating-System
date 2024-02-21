#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CUSTOMERS 5
#define NUM_CHAIRS 3

sem_t barber_semaphore;
sem_t customer_semaphore;
sem_t mutex;
sem_t customerCounterMutex;


int waiting_customers[NUM_CHAIRS];
int front = 0, rear = 0;
int customerCounter=0;

void *barber(void *arg) {
    while (1) {
        //if(customerCounter==MAX_CUSTOMERS)return NULL;
        printf("The barber is sleeping...\n");
        sem_wait(&barber_semaphore);
        sem_wait(&mutex);

        if (front != rear) {
            int customer = waiting_customers[front];
            front = (front + 1) % NUM_CHAIRS;


            printf("The barber is cutting hair for customer %d\n", customer);
            sem_post(&mutex);
            sleep(2);  // Simulate haircut
            printf("The barber has finished cutting hair for customer %d\n", customer);
            sem_post(&customer_semaphore);
        } else {
            sem_post(&mutex);
        }
    }
    return NULL;
}

void *customer(void *arg) {
   while (1)
  
   { int customer_id = *(int *)arg;
    sleep(2);  // Simulate arrival time
    sem_wait(&mutex);

    if ((rear +1 ) % (NUM_CHAIRS) != front) {
        waiting_customers[rear] = customer_id;
        rear = (rear + 1) % NUM_CHAIRS;
        printf("Customer %d is waiting in the waiting room\n", customer_id);
        sem_post(&mutex);

        
        
        sem_post(&barber_semaphore);
        //sem_wait(&customer_semaphore);
        if(customer_id< MAX_CUSTOMERS-1)
        {   
            //sem_post(&barber_semaphore);
            sem_wait(&customer_semaphore);
        }
        printf("Customer %d has finished getting a haircut\n", customer_id);

        // sem_wait(&customerCounterMutex);
        // customerCounter++;
        // sem_post(&customerCounterMutex);

        
        break;
    } else {
        printf("Customer %d is leaving because the waiting room is full\n", customer_id);
        sem_post(&mutex);
    }

   }
   
    return NULL;
}

int main() {

    pthread_t barber_thread, customer_threads[MAX_CUSTOMERS];
    int customer_ids[MAX_CUSTOMERS];

    sem_init(&barber_semaphore, 0, 0);
    sem_init(&customer_semaphore, 0, 0);
    sem_init(&mutex, 0, 1);
    sem_init(&customerCounterMutex,0,1);

    pthread_create(&barber_thread, NULL, barber, NULL);

    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        customer_ids[i] = i;
        pthread_create(&customer_threads[i], NULL, customer, &customer_ids[i]);
    }

   // pthread_join(barber_thread, NULL);

    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        pthread_join(customer_threads[i], NULL);
    }

     pthread_join(barber_thread, NULL);

    
    printf("Done");
    sem_destroy(&barber_semaphore);
    sem_destroy(&customer_semaphore);
    sem_destroy(&mutex);

    return 0;
}
