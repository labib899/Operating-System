#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10
int buffer[N],in=0,out=0;

sem_t F,E,S;
void init() 
{   
    sem_init(&E,0,N);
    sem_init(&F,0,0);
    sem_init(&S,0,0);
}

void insert(int item) 
{
    sem_wait(&E);
    sem_wait(&S);

    buffer[in]=item;
    printf("Produced: %d\n", item);
    in = (in + 1) % N;

    sem_post(&S);
    sem_post(&F);
}

int remove_item() 
{
    sem_wait(&F);
    sem_wait(&S);

    int item = buffer[out];
    out = (out + 1) % N;
    printf("Consumed: %d\n", item);

    sem_post(&S);
    sem_post(&E);
    return item;
}

void *producer_func(void *arg)
{
    for (int i = 0; i < 15; i++) insert(rand()%100);
}

void *consumer_func(void *arg) 
{   
    int item;
    for (int i = 0; i < 15; i++) item = remove_item();
}


int main() 
{
    init();
    pthread_t producer,consumer;
    pthread_create(&producer, NULL, producer_func, NULL);
    pthread_create(&consumer, NULL, consumer_func, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
}
