#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int	N_PHILO = 3;
int	T_DIE = 400 * 1000;
int	T_EAT = 400 * 1000;
int	T_SLEEP = 400 * 1000;
int	N_SIMULATION = 10;
long START, M_START;
int ALL_HAS_CRIETED;
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
pthread_mutex_t	LOCK;
# define EATING 1
# define THNKING 2
# define SLEEPING 3


typedef pthread_t p_t;

typedef struct	s_philo
{
	int				id;
	p_t				*t_id;
	int				status;
	int				last_time_eating;
	struct	s_philo	**tab;
}				t_philo;

int	get_time()
{
	int	time;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec - START) * 1000) + ((tv.tv_usec - M_START) / 1000);
	return (time);
}

void	initial_tab(t_philo **tab, int n)
{	
	int	i;
	t_philo	philo;

	i = -1;
	while (++i < n)
	{
		philo.id = i + 1;
		if ((i + 1) % 2 && i != N_PHILO - 1)
			philo.status = EATING;
		else
			philo.status = THNKING;
		philo.t_id = malloc(sizeof(p_t));
		philo.tab = tab;
		philo.last_time_eating = 0;
		tab[0][i] = philo;
	}
}

int		can_start_eating(t_philo **tab, int index)
{
	int	before;
	int	next;
	int	res;

	res = 0;
	pthread_mutex_lock(&LOCK);
	if (index == 0)
		before = N_PHILO - 1;
	else
		before = index - 1;
	if (index == N_PHILO - 1)
		next = 0;
	else
		next = index++;
	if (tab[0][before].status != EATING && tab[0][next].status != EATING)
		res = 1;
	pthread_mutex_unlock(&LOCK);
	return (res);
}

void	*update_status(void *element)
{
	t_philo *philo = (t_philo *)element;
	struct timeval tv;

	while (ALL_HAS_CRIETED != 1);
	gettimeofday(&tv, NULL);
	if (philo->status == THNKING)
		printf(BLU "%d %d is THNKING \n" RESET, get_time(), philo->id);

	if (philo->status == SLEEPING)
		printf(MAG "%d %d is SLEEPING \n" RESET, get_time(), philo->id);

	int	alredy_thinking = philo->status == THNKING ? 1 : 0;
	while (1)
	{
		if (philo->status == EATING)
		{	
			if (get_time() - philo->last_time_eating > T_DIE / 1000)
				printf(RED "%d %d is DIED \n" RESET, get_time(), philo->id);
			else
				printf(GRN "%d %d is EATING \n" RESET, get_time(), philo->id);
			usleep(T_EAT);
			pthread_mutex_lock(&LOCK);
			philo->status = SLEEPING;
			pthread_mutex_unlock(&LOCK);
		}
		if (philo->status == SLEEPING)
		{	
			printf(MAG "%d %d is SLEEPING \n" RESET, get_time(), philo->id);
			usleep(T_SLEEP);
			pthread_mutex_lock(&LOCK);
			philo->status = THNKING;
			pthread_mutex_unlock(&LOCK);
		}
		if (philo->status == THNKING)
		{	
			if (alredy_thinking == 0)
				printf(BLU "%d %d is THINKING \n" RESET, get_time(), philo->id);
			if (can_start_eating(philo->tab, philo->id - 1))
			{
				alredy_thinking = 0;
				pthread_mutex_lock(&LOCK);
				philo->status = EATING;
				pthread_mutex_unlock(&LOCK);
			}
			else
			alredy_thinking = 1;
		}
	}
	
	return (NULL);
}

void	run_philos(t_philo **tab, int n)
{
	int	i;
	t_philo	philo;

	
	i = -1;
	while (n > ++i)
	{
		p_t *t = malloc(sizeof(p_t));
		pthread_create(tab[0][i].t_id, NULL, update_status, &tab[0][i]);
	}
	struct timeval tv;
	gettimeofday(&tv, NULL);	
	START = tv.tv_sec;
	M_START = tv.tv_usec;
	ALL_HAS_CRIETED = 1;

}
int main(int argc, char const *argv[])
{
	t_philo	*tab;

	tab = malloc(sizeof(t_philo) * (N_PHILO + 1));
	initial_tab(&tab, N_PHILO);
	pthread_mutex_init(&LOCK, NULL);
	ALL_HAS_CRIETED = 0;
	run_philos(&tab, N_PHILO);

	while (1)
	{
	/*	for (size_t i = 0; i < N_PHILO; i++)
		{	
			if (tab[i].status == EATING)
				printf(GRN "from %d status is EATING \n" RESET, tab[i].id);
			else if (tab[i].status == THNKING)
				printf(BLU "from %d status is THINKING \n" RESET, tab[i].id);
			else if (tab[i].status == SLEEPING)
				printf(RED "from %d status is SLEEPING \n" RESET, tab[i].id);
		}
		printf("---------------------------------\n");*/
		
	}
    return 0;

}
