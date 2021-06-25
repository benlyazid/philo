/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 10:21:13 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/25 11:44:46 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int N_PHILO = 5;

void	printing(int i)
{
	sem_t *id = sem_open("write_sem", O_CREAT);
	sem_wait(id);
	int j = 0;
	while (j < 50)
	{
		/* code */
		printf("HI I'AM A THREAD %d\n", i);
		j++;
	}
	printf("--------------------------\n\n");
	//sem_post(id);
}

int main(int argc, char const *argv[])
{
    sem_t *id = sem_open("write_sem", O_CREAT, 777, 0);
	int	i = 0;
	int	r = 1;
    while (i < N_PHILO)
	{
		if (r != 0)
		{
			r = fork();
			if (r == 0)
				printing(i);
		}
			
		else
			wait(NULL);
		i++;
	}
    return 0;
}
