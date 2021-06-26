/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 08:22:49 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/26 08:29:17 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_status_to_eating(t_philo *philo)
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

void	*update_status(void *element)
{
	t_philo	*philo;

	philo = (t_philo *)element;
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
			update_status_to_eating(philo);
		}
	}
	return (NULL);
}
