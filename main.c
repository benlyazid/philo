
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef long long ll;
pthread_mutex_t	lock;
ll COUNTER;
pthread_t tid0, tid1, tid2, tid3, tid4; 

void	ft_put_nbr(int num)
{
	int		base;
	char	c;

	base = 10;
	while (num > base)
	{
		base *= 10;
	}
	base /= 10;
	while (base)
	{
		c =  (num / base) + '0';
		write(1, &c, 1);
		num = num % base;
		base /= 10;
	}
	write(1, "\n", 1);
}

void ft_putstr(char *s)
{
	int i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
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
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int START = tv.tv_sec;
	int M_START = tv.tv_usec;
	int	time;
	int i  = 1;
	int error = 0;
	while (i <= 10)
	{
		usleep((400) * 1000);
		gettimeofday(&tv, NULL);
		time = ((tv.tv_sec - START) * 1000) + ((tv.tv_usec - M_START) / 1000);
		////printf("COUNTER IS %d sleep next   %d\n", time, (400 -  error) * 1000);
		//printf("%d\n", time);
		ft_put_nbr(time);
		i++;
	}
	
	return (0);

}