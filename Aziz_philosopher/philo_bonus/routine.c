/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:58:08 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/15 18:31:05 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_data	*data, int id)
{
	sem_wait(data->forks);
	sem_wait(data->lock_print);
	printf("%lu %d has taken a fork\n", get_time() - data->t, id);
	sem_post(data->lock_print);
	sem_wait(data->forks);
	sem_wait(data->lock_print);
	printf("%lu %d has taken a fork\n", get_time() - data->t, id);
	sem_post(data->lock_print);
}

void	eating(t_data	*data, int id)
{
	sem_wait(data->lock_print);
	printf("%lu %d is eating\n", get_time() - data->t, id);
	data->meals_eated++;
	gettimeofday(&data->last_meal, NULL);
	sem_post(data->lock_print);
	ft_usleep(data->t_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	sleeping(t_data	*data, int id)
{
	sem_wait(data->lock_print);
	printf("%lu %d is sleeping\n", get_time() - data->t, id);
	sem_post(data->lock_print);
	ft_usleep(data->t_sleap);
}

void	thinking(t_data	*data, int id)
{
	sem_wait(data->lock_print);
	printf("%lu %d is thinking\n", get_time() - data->t, id);
	sem_post(data->lock_print);
}

void	routine(t_data	*data, int id)
{
	pthread_t		pid;

	data->id = id;
	gettimeofday(&data->last_meal, NULL);
	pthread_create(&pid, NULL, is_dead, data);
	while (1)
	{
		(taking_forks(data, id));
		(eating(data, id));
		if (finish_meals(data))
			exit (5);
		(sleeping(data, id));
		(thinking(data, id));
	}
}
