/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiakizing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:56:01 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/12 16:07:03 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_philo *philos, t_data *data, pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(&data->lock_time_start, NULL) != 0)
		return (destroy(philos, data, mutex, data->n_philo));
	if (pthread_mutex_init(&data->lock_print, NULL) != 0)
	{
		pthread_mutex_destroy(&data->lock_time_start);
		return (destroy(philos, data, mutex, data->n_philo));
	}
	if (pthread_mutex_init(&data->lock_last_meal, NULL) != 0)
	{
		pthread_mutex_destroy(&data->lock_time_start);
		pthread_mutex_destroy(&data->lock_print);
		return (destroy(philos, data, mutex, data->n_philo));
	}
	if (pthread_mutex_init(&data->lock_die, NULL) != 0)
	{
		pthread_mutex_destroy(&data->lock_time_start);
		pthread_mutex_destroy(&data->lock_print);
		pthread_mutex_destroy(&data->lock_last_meal);
		return (destroy(philos, data, mutex, data->n_philo));
	}
	return (0);
}
