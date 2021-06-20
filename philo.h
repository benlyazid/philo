/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 12:27:13 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/20 12:53:07 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
typedef pthread_t p_t;
typedef	pthread_mutex_t p_m_t;

typedef struct	s_philo
{
	int				id;
	p_t				*t_id;
	int				status;
	int				last_time_eating;
	struct	s_philo	**tab;
	p_m_t			**fork_loks;
	int				simulation;
    p_m_t           *write_lock;
}				t_philo;

void    ft_putstr(char *s);
void    ft_put_nbr(int num);
void    ft_put_status(int time, int id, char *status, char *clr, p_m_t *write_lock);

#endif