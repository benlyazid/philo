/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_visor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 08:30:40 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/26 09:30:27 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*philo_is_died(t_philo *philos, int i)
{
	ft_put_died(get_time(philos), i + 1, philos[i].write_lock);
	pthread_mutex_lock(philos[i].write_lock);
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
				if (get_time(philos) - philos[i].last_time_eating
					> philos[i].data.T_DIE / 1000)
					return (philo_is_died(philos, i));
				pthread_mutex_unlock(philos[i].is_eating);
			}
			usleep(200);
		}
		if (!check_simulation_count(&philos))
			return (0);
	}
	return (NULL);
}
