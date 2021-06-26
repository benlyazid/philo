/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 12:27:13 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/26 08:52:50 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

# define EATING 1
# define THNKING 2
# define SLEEPING 3

typedef pthread_t		t_p_t;
typedef pthread_mutex_t	t_p_m_t;

typedef struct s_data
{
	int	N_PHILO;
	int	T_DIE;
	int	T_EAT;
	int	T_SLEEP;
	int	N_SIMULATION;
	int	check;
}				t_data;

typedef struct s_philo
{
	int				id;
	t_p_t			*t_id;
	int				status;
	int				last_time_eating;
	struct s_philo	**tab;
	t_p_m_t			**fork_loks;
	int				simulation;
	t_p_m_t			*write_lock;
	t_p_m_t			*is_eating;
	t_data			data;
	long			START;
	long			U_START;
}				t_philo;

void	ft_putstr(char *s);
void	ft_put_nbr(int num);
int		ft_usleep(int delay);
int		ft_atoi(char *str, int *check);
int		get_time(t_philo *tab);
void	ft_put_died(int time, int id, t_p_m_t *write_lock);
void	ft_put_thinking(int time, int id, t_p_m_t *write_lock);
void	ft_put_sleeping(int time, int id, t_p_m_t *write_lock);
void	ft_put_eating(int time, int id, t_p_m_t *write_lock);
void	ft_put_take_fork(int time, int id, t_p_m_t *write_lock);
int		take_fork(t_philo **tab, int index);
int		drope_fork(t_philo **tab, int index);
void	*update_status(void *element);
void	*start_super_visor(void *elmnts);
int		check_simulation_count(t_philo **tab);
int		get_time(t_philo *tab);

#endif