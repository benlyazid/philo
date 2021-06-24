/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:15:24 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/24 13:39:00 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	get_time(t_philo *tab)
{
	int	time;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec - tab->START) * 1000) + ((tv.tv_usec -  tab->U_START) / 1000);
	return (time);
}

t_philo	set_philo(p_m_t	**forks, p_m_t *write_locks, int i, t_data data)
{
	t_philo	philo;

	philo.id = i + 1;
	philo.status = -1;
	philo.t_id = malloc(sizeof(p_t));
	forks[i] = malloc(sizeof(p_m_t));
	pthread_mutex_init(forks[i], NULL);
	philo.fork_loks = forks;
	philo.last_time_eating = 0;
	philo.simulation = 0;
	philo.is_eating = malloc(sizeof(p_m_t));
	pthread_mutex_init(philo.is_eating, NULL);
	philo.write_lock = write_locks;
	philo.data = data;
	return (philo);
}

void	initial_tab(t_philo **tab, int n, t_data data)
{	
	int		i;
	t_philo	philo;
	p_m_t	**forks;
	p_m_t	*write_locks;

	forks = malloc(sizeof(p_m_t *) * n);
	write_locks = malloc(sizeof(p_m_t));
	pthread_mutex_init(write_locks, NULL);

	i = -1;
	while (++i < n)
	{
		philo = set_philo(forks, write_locks, i, data);
		philo.tab = tab;
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
	ft_put_take_fork(get_time(*tab), index + 1, tab[0]->write_lock);
	pthread_mutex_lock(tab[0][index].fork_loks[next]);
	ft_put_take_fork(get_time(*tab), index + 1, tab[0]->write_lock);
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
			ft_put_sleeping(get_time(philo), philo->id, philo->write_lock);
			philo->status = SLEEPING;
			ft_usleep(philo->data.T_SLEEP);
		}
		if (philo->status == SLEEPING)
		{	
			ft_put_thinking(get_time(philo), philo->id, philo->write_lock);
			philo->status = THNKING;
		}
		if (philo->status == THNKING || philo->status == -1)
		{
			take_fork(philo->tab, philo->id - 1);
			pthread_mutex_lock(philo->is_eating);
			philo->last_time_eating = get_time(philo);
			ft_put_eating(get_time(philo), philo->id, philo->write_lock);
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
	i = -1;
	while (n > ++i)
	{
		tab[0][i].START = tv.tv_sec;
		tab[0][i].U_START = tv.tv_usec;
	}
}

int	check_simulation_count(t_philo **tab)
{
	int	i;

	i = 0;
	if (tab[0][i].data.N_SIMULATION == -1)
		return (1);
	while (i < tab[0][i].data.N_SIMULATION)
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
	int		i;

	philos = (t_philo *)elmnts;
	while (1)
	{
		i = -1;
		while (++i < philos[0].data.N_PHILO)
		{
			if (philos[i].status != EATING)
			{
				pthread_mutex_lock(philos[i].is_eating);
				if (get_time(philos) - philos[i].last_time_eating > philos[i].data.T_DIE / 1000)
				{
					ft_put_died(get_time(philos), i + 1, philos[i].write_lock);
					pthread_mutex_lock(philos[i].write_lock);
					return (0);
				}
				pthread_mutex_unlock(philos[i].is_eating);
			}
		}
		if (!check_simulation_count(&philos))
			return (0);
		usleep(800);
	}
	return (NULL);
}

t_data	get_data(char **argv, int argc)
{
	t_data	data;
	int		check;

	data.check = 1;
	if (argc < 5 || argc > 6)
	{
		data.check = -1;
		return (data);
	}
	check = 1;
	data.N_PHILO = ft_atoi(argv[1], &check);
	data.T_DIE = ft_atoi(argv[2], &check) * 1000;
	data.T_EAT = ft_atoi(argv[3], &check) * 1000;
	data.T_SLEEP = ft_atoi(argv[4], &check) * 1000;
	data.N_SIMULATION = -1;
	if (argc == 6)	
		data.N_SIMULATION = ft_atoi(argv[5], &check);
	if (check == -1)
		data.check = -1;
	return (data);
}

int main(int argc, char const *argv[])
{
	t_philo	*tab;
	p_t		*super_visor;
	t_data	data;
	int		super_visor_check;

	super_visor_check = 1;
	data =  get_data((char **)argv, argc);
	if (data.check == -1)
		return (0);
	tab = malloc(sizeof(t_philo) * (data.N_PHILO));
	super_visor = malloc(sizeof(p_t));

	initial_tab(&tab, data.N_PHILO, data);
	run_philos(&tab, data.N_PHILO);
	pthread_create(super_visor, NULL, start_super_visor, tab);
	pthread_join(*super_visor, NULL);
    return 0;

}    