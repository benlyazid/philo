/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 12:27:28 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/22 13:10:37 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_usleep(int delay)
{
	struct	timeval tv;
	int	start, m_start, time, split, i;
	int	err;

	//delay *= 1000;
	//usleep(delay);
	//return 0;
	err = 0;
	split = 10;
	i = 1;
	gettimeofday(&tv, NULL);
	start = tv.tv_sec;
	m_start = tv.tv_usec;
	while (i <= split)
	{
		usleep((delay / split) - err);
		gettimeofday(&tv, NULL);
		time = ((tv.tv_sec - start) * 1000000) + ((tv.tv_usec - m_start)); //time in u_s
		err = (time) - ((delay / split) * i); //err in u_s
		i++;
	}
	return (1);
}

int		ft_atoi(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = (num  * 10) + (str[i] - '0');
		else
			exit(0);
		if (num > INT32_MAX)
			exit(0);
		i++;
	}
	return (num);
}

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