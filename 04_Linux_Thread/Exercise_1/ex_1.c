#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#define THREAD_NUM  (2)

void *thread_func(void *arg)
{
    (void)arg;

    printf("Thread ID %lu is running\n", (uint64_t)pthread_self());

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

    return EXIT_SUCCESS;
}