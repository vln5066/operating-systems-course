#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1_func(void *arg) {
    pthread_mutex_lock(&mutex1);
    printf("Thread 1 acquired mutex1\n");
    sleep(1); // Simulate some work

    printf("Thread 1 waiting for mutex2\n");
    pthread_mutex_lock(&mutex2); // Deadlock happens here
    printf("Thread 1 acquired mutex2\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void *thread2_func(void *arg) {
    pthread_mutex_lock(&mutex2);
    printf("Thread 2 acquired mutex2\n");
    sleep(1); // Simulate some work

    printf("Thread 2 waiting for mutex1\n");
    pthread_mutex_lock(&mutex1); // Deadlock happens here
    printf("Thread 2 acquired mutex1\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

