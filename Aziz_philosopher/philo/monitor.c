/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:34:58 by afadouac          #+#    #+#             */
/*   Updated: 2024/10/22 18:19:41 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meals_eated(t_philo *philo, t_data *data)
{
	int	i;

	if (data->meals == -1)
		return (0);
	i = 0;
	while (i < data->n_philo)
	{
		if (philo[i].meals_eaten < data->meals)
			return (0);
		i++;
	}
	return (1);
}

void	monitor(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		LOCK(&data->lock_last_meal);
		LOCK(&data->lock_die);
		if ((philo[i].last_meal != 0 && \
			(get_time() - philo[i].last_meal > data->t_die)) || \
				meals_eated(philo, data))
		{
			data->die = 1;
			UNLOCK(&data->lock_last_meal);
			UNLOCK(&data->lock_die);
			break ;
		}
		i++;
		i = i % data->n_philo;
		UNLOCK(&data->lock_last_meal);
		UNLOCK(&data->lock_die);
	}
	data->die_index = i;
	if (meals_eated(philo, data))
		data->die_index = -1;
	data->death_time = get_time();
}
