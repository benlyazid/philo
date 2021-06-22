/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 12:27:13 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/22 15:23:19 by kbenlyaz         ###   ########.fr       */
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

# define EATING 1
# define THNKING 2
# define SLEEPING 3

typedef pthread_t p_t;
typedef	pthread_mutex_t p_m_t;


typedef	struct s_data
{
	int	N_PHILO;
	int	T_DIE;
	int	T_EAT;
	int	T_SLEEP;
	int	N_SIMULATION;
}			t_data;

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
	p_m_t			*is_eating;
	t_data			data;
}				t_philo;

void    ft_putstr(char *s);
void    ft_put_nbr(int num);
void    ft_put_status(int time, int id, char *status, char *clr, p_m_t *write_lock);
int		ft_usleep(int delay);
int		ft_atoi(char *str);

#endif