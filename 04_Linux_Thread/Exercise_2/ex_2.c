#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#define THREAD_NUM  (3)

long long int counter = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *arg)
{
    (void)arg;

    uint32_t i;

    for (i = 0U; i < 1000000U; i++)
    {
        pthread_mutex_lock(&mtx);
        counter++;
        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

int32_t main()
{
    pthread_t thread_id[THREAD_NUM];
    int8_t i;

    for (i = 0; i < THREAD_NUM; i++)
    {
        (void)pthread_create(&thread_id[i], NULL, &thread_func, NULL);
    }

    for (i = 0; i < THREAD_NUM; i++)
    {
        (void)pthread_join(thread_id[i], NULL);
    }

    pthread_mutex_destroy(&mtx);

    printf("Counter = %lld\n", counter);

    return EXIT_SUCCESS;
}