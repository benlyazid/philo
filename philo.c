#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "./philo.h"

// int	N_PHILO = 4;
// int	T_DIE = (410) * 1000;
// int	T_EAT = (200) * 1000;
// int	T_SLEEP = (200) * 1000;
// int	N_SIMULATION = 5000;

long START, M_START;
int ALL_HAS_CRIETED;



int	get_time()
{
	int	time;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec - START) * 1000) + ((tv.tv_usec - M_START) / 1000);
	return (time);
}

void	initial_tab(t_philo **tab, int n, t_data data)
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
		philo.is_eating = malloc(sizeof(p_m_t));
		pthread_mutex_init(philo.is_eating, NULL);
		philo.write_lock = write_locks;
		philo.data = data;
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
		before = tab[0]->data.N_PHILO - 1;
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
		before = tab[0]->data.N_PHILO - 1;
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
		usleep(800);
	while (1)
	{
		if (philo->status == EATING)
		{	
			ft_put_status(get_time(), philo->id, "is sleeping", MAG, philo->write_lock);
			philo->status = SLEEPING;
			ft_usleep(philo->data.T_SLEEP);

		}
		if (philo->status == SLEEPING)
		{	
			ft_put_status(get_time(), philo->id, "is thinking", BLU, philo->write_lock);
			philo->status = THNKING;
		}
		if (philo->status == THNKING || philo->status == -1)
		{
			take_fork(philo->tab, philo->id - 1);
			pthread_mutex_lock(philo->is_eating);
			philo->last_time_eating = get_time();
			ft_put_status(get_time(), philo->id, "is eating", GRN, philo->write_lock);
			philo->status = EATING;
			ft_usleep(philo->data.T_EAT);
			pthread_mutex_unlock(philo->is_eating);
			drope_fork(philo->tab, philo->id - 1);
			philo->simulation++;
		}
	}
	
	return (NULL);
}

void	run_philos(t_philo **tab, int n)
{
	int	i;
	struct timeval tv;
	
	i = -1;
	while (n > ++i)
	{
		pthread_create(tab[0][i].t_id, NULL, update_status, &tab[0][i]);
	}
	gettimeofday(&tv, NULL);	
	START = tv.tv_sec;
	M_START = tv.tv_usec;

}

int	check_simulation_count(t_philo **tab)
{
	int	i;

	i = 0;
	while (i < tab[0][i].data.N_PHILO)
	{
		if (tab[0][i].simulation < tab[0][i].data.N_SIMULATION)
			return (1);
		i++;
	}
	return (0);

}

void	*start_super_visor(void *elmnts)
{
	t_philo	*philos;
	int	i;
	philos = (t_philo *)elmnts;
	while (1)
	{
		i = 0;
		while (i < philos[i].data.N_PHILO)
		{
			if (philos[i].status == EATING)
					continue ;
			pthread_mutex_lock(philos[i].is_eating);
			if (get_time() - philos[i].last_time_eating > philos[i].data.T_DIE / 1000)
			{
				ft_put_status(get_time(), i + 1, "IS DIED", RED, philos[i].write_lock);
				exit(0);
			}
			pthread_mutex_unlock(philos[i].is_eating);
			usleep(800);
			i++;
		}

	}
	return (NULL);
}

t_data	get_data(char **argv, int argc)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		exit(0);
	data.N_PHILO = ft_atoi(argv[1]);
	data.T_DIE = ft_atoi(argv[2]);
	data.T_EAT = ft_atoi(argv[3]);
	data.T_SLEEP = ft_atoi(argv[4]);
	data.N_SIMULATION = -1;
	if (argc == 6)	
		data.N_SIMULATION = ft_atoi(argv[5]);

	return (data);
}

int main(int argc, char const *argv[])
{
	t_philo	*tab;
	p_t		*super_visor;
	t_data data;

	data =  get_data((char **)argv, argc);
	tab = malloc(sizeof(t_philo) * (data.N_PHILO));
	super_visor = malloc(sizeof(p_t));

	initial_tab(&tab, data.N_PHILO, data);
	run_philos(&tab, data.N_PHILO);
	pthread_create(super_visor, NULL, start_super_visor, tab);
	while (check_simulation_count(&tab))
		usleep(800);
    return 0;

}