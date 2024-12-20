/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_doing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:51:41 by nthoach           #+#    #+#             */
/*   Updated: 2024/10/24 19:31:16 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_data	*data, int id)
{
	sem_wait(data->lock_forks);
	sem_wait(data->lock_print);
	printf("%lu %d has taken a fork\n", timeslap() - data->t_start, id);
	sem_post(data->lock_print);
	sem_wait(data->lock_forks);
	sem_wait(data->lock_print);
	printf("%lu %d has taken a fork\n", timeslap() - data->t_start, id);
	sem_post(data->lock_print);
}

void	eating(t_data	*data, int id)
{
	sem_wait(data->lock_print);
	printf("%lu %d is eating\n", timeslap() - data->t_start, id);
	sem_post(data->lock_print);
	sem_wait(data->lock_death);
	data->n_ate++;
	data->t_lastmeal = timeslap();
	sem_post(data->lock_death);
	ft_usleep(data->t2eat);
	sem_post(data->lock_forks);
	sem_post(data->lock_forks);
}

void	sleeping(t_data	*data, int id)
{
	sem_wait(data->lock_print);
	printf("%lu %d is sleeping\n", timeslap() - data->t_start, id);
	sem_post(data->lock_print);
	ft_usleep(data->t2sleep);
}

void	thinking(t_data	*data, int id)
{
	sem_wait(data->lock_print);
	printf("%lu %d is thinking\n", timeslap() - data->t_start, id);
	sem_post(data->lock_print);
}

void	doing(t_data	*data, int id)
{
	pthread_t		pid;

	data->id = id;
	sem_wait(data->lock_death);
	data->t_lastmeal = timeslap();
	sem_post(data->lock_death);
	pthread_create(&pid, NULL, check_die, data);
	while (1)
	{
		taking_forks(data, id);
		eating(data, id);
		if (check_full(data))
			exit (5);
		sleeping(data, id);
		thinking(data, id);
	}
}
