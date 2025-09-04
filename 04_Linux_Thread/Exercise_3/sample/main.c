#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg);
void *consumer(void *arg);

int32_t g_data;
bool g_data_ready = false;

void *producer(void *arg)
{
	(void)arg;
	for (int8_t i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mtx);
		while (true == g_data_ready)
		{
			pthread_cond_wait(&cond, &mtx);
		}
		g_data = rand();
		g_data_ready = true;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

void *consumer(void *arg)
{
	(void)arg;
	for (int8_t i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&mtx);
		while (false == g_data_ready)
		{
			pthread_cond_wait(&cond, &mtx);
		}
		printf("g_data = %d\n", g_data);
		g_data_ready = false;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int32_t main()
{
	pthread_t producer_thread;
	pthread_t consumer_thread;

	srand(time(NULL));

	pthread_create(&producer_thread, NULL, &producer, NULL);
	pthread_create(&consumer_thread, NULL, &consumer, NULL);

	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);    

    return 0;
}