#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (philosopher_id + 1) % NUM_PHILOSOPHERS

int state[NUM_PHILOSOPHERS];
int philosopher_id[NUM_PHILOSOPHERS];

sem_t mutex;
sem_t semaphore[NUM_PHILOSOPHERS];

void test(int philosopher_id)
{
    if (state[philosopher_id] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING) {
        // Philosopher can eat now
        state[philosopher_id] = EATING;

        sleep(1);

        printf("Philosopher %d picks up forks %d and %d\n",
            philosopher_id + 1, LEFT + 1, philosopher_id + 1);

        printf("Philosopher %d is Eating\n", philosopher_id + 1);

        // Notify other hungry philosophers
       sem_post(&semaphore[philosopher_id]);
    }
}

void pick_up_forks(int philosopher_id)
{
    sem_wait(&mutex);

    // Set philosopher's state to hungry
    state[philosopher_id] = HUNGRY;

    printf("Philosopher %d is Hungry\n", philosopher_id + 1);

    // Try to eat if neighbors are not eating
    test(philosopher_id);

    sem_post(&mutex);

    // If unable to eat, wait to be signaled
    sem_wait(&semaphore[philosopher_id]);

    sleep(1);
}

void put_down_forks(int philosopher_id)
{
    sem_wait(&mutex);

    // Set philosopher's state to thinking
    state[philosopher_id] = THINKING;

    printf("Philosopher %d puts down forks %d and %d\n",
        philosopher_id + 1, LEFT + 1, philosopher_id + 1);

    printf("Philosopher %d is thinking\n", philosopher_id + 1);

    // Notify neighbors that forks are available
    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void* dining_philosopher(void* id)
{
    int* philosopher_id = id;

    while (1) {
        sleep(1);
        pick_up_forks(*philosopher_id);
        sleep(1);
        put_down_forks(*philosopher_id);
    }
}

int main()
{
    int i;
    pthread_t philosopher_thread[NUM_PHILOSOPHERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);

    for (i = 0; i < NUM_PHILOSOPHERS; i++)
      {  sem_init(&semaphore[i], 0, 0);
         philosopher_id[i]=i;
      }   

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosopher_thread[i], NULL, dining_philosopher, &philosopher_id[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosopher_thread[i], NULL);

    return 0;
}
