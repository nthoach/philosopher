/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_set_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:37 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/24 12:41:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_all(t_data *data, t_philo *philo, pthread_mutex_t *forks, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(forks + j);
		j++;
	}
	free_mem(data, philo, forks);
	return (1);
}

int	ini_locks(t_data *data)
{
	if (pthread_mutex_init(&data->lock_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->lock_checktime, NULL))
	{
		pthread_mutex_destroy(&data->lock_print);
		return (1);
	}
	if (pthread_mutex_init(&data->lock_checkdie, NULL))
	{
		pthread_mutex_destroy(&data->lock_print);
		pthread_mutex_destroy(&data->lock_checktime);
		return (1);
	}
	if (pthread_mutex_init(&data->lock_checkfull, NULL))
	{
		pthread_mutex_destroy(&data->lock_print);
		pthread_mutex_destroy(&data->lock_checktime);
		pthread_mutex_destroy(&data->lock_checkdie);
		return (1);
	}
	return (0);
}

void	init_philo(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philo[i].death = 0;
		philo[i].id = i + 1;
		philo[i].n_ate = 0;
		philo[i].t_lastmeal = 0;
		philo[i].right = &forks[i];
		philo[i].left = &forks[(i + 1) % data->n_philo];
		philo[i].data = data;
		i++;
	}
}

int	ini_lock_philo(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	int				i;

	i = -1;
	while (++i < data->n_philo)
		if (pthread_mutex_init(&forks[i], NULL))
			return (destroy_all(data, philo, forks, i));
	if (ini_locks(data))
		return (destroy_all(data, philo, forks, data->n_philo));
	init_philo(data, philo, forks);
	return (OK);
}
