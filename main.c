
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef long long ll;
pthread_mutex_t	lock;
ll COUNTER;
pthread_t tid0, tid1, tid2, tid3, tid4; 


int sold = 100;
void ft_putstr(char *s)
{
	int i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}

}
void *counting_2(void *v)
{
	for (ll i = 10000; i < 20000; i++)
	{
		pthread_mutex_lock(&lock);
		COUNTER++;
		pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

void *counting_1(void *v)
{

	for (ll i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&lock);
		COUNTER++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

void *print()
{
	while (COUNTER < 100000);
	ft_putstr("abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
	return 0;
}

void *check()
{
	while(COUNTER  < 250)
	{
		//printf("222222222222222\n");
		//usleep(1);
	}
	pthread_cancel(tid0);
	return NULL;
}

int main()
{
	COUNTER = 0;
	/*pthread_create(&tid0, NULL, counting, NULL);
	pthread_create(&tid1, NULL, check, NULL);
	pthread_join(tid0, NULL);
	pthread_join(tid1, NULL);
	// pthread_cancel(tid0);
	// pthread_join(tid0, NULL);
	// while(COUNTER  < 1147483647 / 2);
	printf("counter is %llu\n", COUNTER);*/

	pthread_mutex_init(&lock, NULL);

	pthread_create(&tid1, NULL, counting_1, NULL);

	pthread_create(&tid2, NULL, counting_2, NULL);
	pthread_join(tid1, NULL);

	pthread_join(tid2, NULL);

	printf("COUNTER IS %llu\n", COUNTER);
	return (0);

}