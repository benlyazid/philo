/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:15:24 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/26 09:13:22 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_philo	set_philo(t_p_m_t	**forks, t_p_m_t *write_locks, int i, t_data data)
{
	t_philo	philo;

	philo.id = i + 1;
	philo.status = -1;
	philo.t_id = malloc(sizeof(t_p_t));
	forks[i] = malloc(sizeof(t_p_m_t));
	pthread_mutex_init(forks[i], NULL);
	philo.fork_loks = forks;
	philo.last_time_eating = 0;
	philo.simulation = 0;
	philo.is_eating = malloc(sizeof(t_p_m_t));
	pthread_mutex_init(philo.is_eating, NULL);
	philo.write_lock = write_locks;
	philo.data = data;
	return (philo);
}

void	initial_tab(t_philo **tab, int n, t_data data)
{	
	int		i;
	t_philo	philo;
	t_p_m_t	**forks;
	t_p_m_t	*write_locks;

	forks = malloc(sizeof(t_p_m_t *) * n);
	write_locks = malloc(sizeof(t_p_m_t));
	pthread_mutex_init(write_locks, NULL);
	i = -1;
	while (++i < n)
	{
		philo = set_philo(forks, write_locks, i, data);
		philo.tab = tab;
		tab[0][i] = philo;
	}
}

void	run_philos(t_philo **tab, int n)
{
	int				i;
	struct timeval	tv;

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
	if (data.N_PHILO == 0)
		data.check = -1;
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

int	main(int argc, char const *argv[])
{
	t_philo	*tab;
	t_p_t	*super_visor;
	t_data	data;
	int		super_visor_check;

	super_visor_check = 1;
	data = get_data((char **)argv, argc);
	if (data.check == -1)
		return (0);
	tab = malloc(sizeof(t_philo) * (data.N_PHILO));
	super_visor = malloc(sizeof(t_p_t));
	initial_tab(&tab, data.N_PHILO, data);
	run_philos(&tab, data.N_PHILO);
	pthread_create(super_visor, NULL, start_super_visor, tab);
	pthread_join(*super_visor, NULL);
	return (0);
}
