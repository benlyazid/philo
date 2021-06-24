/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbenlyaz <kbenlyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:27:57 by kbenlyaz          #+#    #+#             */
/*   Updated: 2021/06/24 13:28:19 by kbenlyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_put_take_fork(int time, int id, p_m_t *write_lock)
{
    pthread_mutex_lock(write_lock); 
    ft_putstr(CYN);
    ft_put_nbr(time);
    ft_putstr(" ");
    ft_put_nbr(id);
    ft_putstr(" ");
    ft_putstr("has taken a fork");
    write(1, "\n", 1);
    ft_putstr(RESET);
    pthread_mutex_unlock(write_lock);
}

void    ft_put_eating(int time, int id, p_m_t *write_lock)
{
    pthread_mutex_lock(write_lock); 
    ft_putstr(GRN);
    ft_put_nbr(time);
    ft_putstr(" ");
    ft_put_nbr(id);
    ft_putstr(" ");
    ft_putstr("is eating");
    write(1, "\n", 1);
    ft_putstr(RESET);
    pthread_mutex_unlock(write_lock);
}

void    ft_put_sleeping(int time, int id, p_m_t *write_lock)
{
    pthread_mutex_lock(write_lock); 
    ft_putstr(MAG);
    ft_put_nbr(time);
    ft_putstr(" ");
    ft_put_nbr(id);
    ft_putstr(" ");
    ft_putstr("is sleeping");
    write(1, "\n", 1);
    ft_putstr(RESET);
    pthread_mutex_unlock(write_lock);
}

void    ft_put_thinking(int time, int id, p_m_t *write_lock)
{
    pthread_mutex_lock(write_lock); 
    ft_putstr(BLU);
    ft_put_nbr(time);
    ft_putstr(" ");
    ft_put_nbr(id);
    ft_putstr(" ");
    ft_putstr("is thinking");
    write(1, "\n", 1);
    ft_putstr(RESET);
    pthread_mutex_unlock(write_lock);
}

void    ft_put_died(int time, int id, p_m_t *write_lock)
{
    pthread_mutex_lock(write_lock); 
    ft_putstr(RED);
    ft_put_nbr(time);
    ft_putstr(" ");
    ft_put_nbr(id);
    ft_putstr(" ");
    ft_putstr("is died");
    write(1, "\n", 1);
    ft_putstr(RESET);
    pthread_mutex_unlock(write_lock);
}
