/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 12:27:28 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/24 13:28:06 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_usleep(int delay)
{
	struct	timeval tv;
	int	start, m_start, time, split, i, delay_1;
	int	err;

	err = 0;
	split = 10;
	i = 1;
	delay_1 = delay - 10000;
	gettimeofday(&tv, NULL);
	start = tv.tv_sec;
	m_start = tv.tv_usec;
	usleep(delay_1);
	
	while (1)
	{
		gettimeofday(&tv, NULL);
		time = ((tv.tv_sec - start) * 1000000) + ((tv.tv_usec - m_start)); //time in u_s
		if (time >= delay)
			return (1);
	}
	return (1);
}


int		ft_atoi(char *str, int *check)
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
		{
			*check = -1;	
			return 0;
		}
		if (num > INT32_MAX)
		{
			*check = -1;	
			return (0);
		}
		i++;
	}
	return (num);
}

void	ft_put_nbr(int num)
{
	int		base;
	char	c;

	base = 10;
	while (num >= base)
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

