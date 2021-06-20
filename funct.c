/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 12:27:28 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/20 12:49:03 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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

void    ft_put_status(int time, int id, char *status, char *clr, p_m_t *write_lock)
{
    pthread_mutex_lock(write_lock);
    ft_putstr(clr);
    ft_put_nbr(time);
    ft_putstr(" ");
    ft_put_nbr(id);
    ft_putstr(" ");
    ft_putstr(status);
    write(1, "\n", 1);
    ft_putstr(RESET);
    pthread_mutex_unlock(write_lock);
}