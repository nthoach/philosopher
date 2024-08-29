/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:30:20 by afadouac          #+#    #+#             */
/*   Updated: 2024/08/10 09:30:44 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

int	finish_meals(t_data *data)
{
	int	meals;

	sem_wait(data->death);
	meals = data->meals_eated;
	if (data->meals < 0 || meals < data->meals)
	{
		sem_post(data->death);
		return (0);
	}
	sem_post(data->death);
	data->die = 1;
	sem_post(data->lock_print);
	return (1);
}

void	*is_dead(void *data1)
{
	t_data			*data;
	size_t			def;
	struct timeval	courant;

	data = (t_data *)data1;
	while (1)
	{
		sem_wait(data->lock_print);
		gettimeofday(&courant, NULL);
		def = (courant.tv_sec * 1000 + courant.tv_usec / 1000) \
				- (data->last_meal.tv_sec * 1000 + \
					data->last_meal.tv_usec / 1000);
		if (def > data->t_die)
		{
			printf("%lu %d died\n", get_time() - data->t, data->id);
			exit (0);
		}
		sem_post(data->lock_print);
		ft_usleep(200);
	}
	return (NULL);
}
