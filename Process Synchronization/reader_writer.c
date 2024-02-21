#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define READERS 4
#define WRITERS 3
pthread_mutex_t mutex,write_mutex;
int rc = 0;

void init()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&write_mutex,NULL);
}

void *reader(void *arg) 
{
    while (1) 
    {
        pthread_mutex_lock(&mutex);
        rc++;
        if (rc == 1) pthread_mutex_lock(&write_mutex);
        pthread_mutex_unlock(&mutex);

        printf("Reader is reading\n"); usleep(rand() % 1000000);

        pthread_mutex_lock(&mutex);
        rc--;
        if (rc == 0) pthread_mutex_unlock(&write_mutex);
        pthread_mutex_unlock(&mutex);

        usleep(rand() % 1000000);
    }
}

void *writer(void *arg) 
{
    while (1) 
    {
        pthread_mutex_lock(&write_mutex);
        printf("Writer is writing\n"); usleep(rand() % 1000000);
        pthread_mutex_unlock(&write_mutex);

        usleep(rand() % 1000000);
    }
}


int main() 
{   
    init();
    pthread_t reader_threads[READERS], writer_threads[WRITERS];
    for (int i = 0; i < READERS; i++) pthread_create(&reader_threads[i], NULL, reader, NULL);
    for (int i = 0; i < WRITERS; i++) pthread_create(&writer_threads[i], NULL, writer, NULL);

    for (int i = 0; i < READERS; i++) pthread_join(reader_threads[i], NULL);
    for (int i = 0; i < WRITERS; i++) pthread_join(writer_threads[i], NULL);
}
