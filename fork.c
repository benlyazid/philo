/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 08:22:49 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/26 08:23:57 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo **tab, int index)
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

int	drope_fork(t_philo **tab, int index)
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
