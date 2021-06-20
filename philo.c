#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "./philo.h"
int	N_PHILO = 3;
int T_ERR = 1;
int	T_DIE = (400) * 1000;
int	T_EAT = (400) * 1000;
int	T_SLEEP = (400) * 1000;
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
# define EATING 1
# define THNKING 2
# define SLEEPING 3




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
	p_m_t	**forks;
	p_m_t	*write_locks;


	forks = malloc(sizeof(p_m_t *) * n);
	write_locks = malloc(sizeof(p_m_t));
	pthread_mutex_init(write_locks, NULL);

	i = -1;
	while (++i < n)
	{
		philo.id = i + 1;
		philo.status = -1;
		philo.t_id = malloc(sizeof(p_t));
		forks[i] = malloc(sizeof(p_m_t));
		pthread_mutex_init(forks[i], NULL);
		philo.tab = tab;
		philo.fork_loks = forks;
		philo.last_time_eating = 0;
		philo.simulation = 0;
		philo.write_lock = write_locks;
		tab[0][i] = philo;
	}
}

int		take_fork(t_philo **tab, int index)
{
	int	before;
	int	next;
	int	res;

	res = 0;
	if (index == 0)
		before = N_PHILO - 1;
	else
		before = index - 1;
	next = index;
	pthread_mutex_lock(tab[0][index].fork_loks[before]);
	ft_put_status(get_time(),index + 1, "has taken a fork", CYN, tab[0]->write_lock);
	
	pthread_mutex_lock(tab[0][index].fork_loks[next]);
	ft_put_status(get_time(),index + 1, "has taken a fork", CYN, tab[0]->write_lock);
	return (res);
}

int		drope_fork(t_philo **tab, int index)
{
	int	before;
	int	next;
	int	res;

	res = 0;
	if (index == 0)
		before = N_PHILO - 1;
	else
		before = index - 1;
	next = index;
	pthread_mutex_unlock(tab[0][index].fork_loks[before]);
	pthread_mutex_unlock(tab[0][index].fork_loks[next]);
	return (res);
}

void	*update_status(void *element)
{
	t_philo	*philo = (t_philo *)element;
	if (philo->id % 2)
		usleep(1000);
	while (philo->simulation < 3)
	{
		if (philo->status == EATING)
		{	
			ft_put_status(get_time(), philo->id, "is sleeping", MAG, philo->write_lock);
			philo->status = SLEEPING;
			usleep(T_SLEEP);

		}
		if (philo->status == SLEEPING)
		{	
			ft_put_status(get_time(), philo->id, "is thinking", BLU, philo->write_lock);
			philo->status = THNKING;
		}
		if (philo->status == THNKING || philo->status == -1)
		{
			take_fork(philo->tab, philo->id - 1);
			ft_put_status(get_time(), philo->id, "is eating", GRN, philo->write_lock);
			philo->status = EATING;
			usleep(T_EAT);
			drope_fork(philo->tab, philo->id - 1);
			philo->simulation++;
		}
	}
	//exit(1);
	
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

}

int main(int argc, char const *argv[])
{
	t_philo	*tab;

	tab = malloc(sizeof(t_philo) * (N_PHILO + 1));
	initial_tab(&tab, N_PHILO);
	ALL_HAS_CRIETED = 0;
	run_philos(&tab, N_PHILO);

	while (1)
	{
	}
    return 0;

}
