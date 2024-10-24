/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_simulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:16:01 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/24 15:38:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulate_philo(t_data *data, pid_t *philo)
{
	int		i;

	i = 0;
	data->t_start = timeslap();
	while (i < data->n_philo)
	{
		philo[i] = fork();
		if (philo[i] == 0)
			doing(data, i + 1);
		if (philo[i] < 0)
			errors(ER_FORK, data, philo);
		i++;
	}
	waiting(data);
}

int	finish_meals(t_data *data)
{
	int	meals;

	sem_wait(data->lock_death);
	meals = data->n_ate;
	if (data->max_meal < 0 || meals < data->max_meal)
	{
		sem_post(data->lock_death);
		return (0);
	}
	sem_post(data->lock_death);
	data->die = 1;
	sem_post(data->lock_print);
	return (1);
}

void	*checkdie(void *data1)
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
				- (data->t_lastmeal.tv_sec * 1000 + \
					data->t_lastmeal.tv_usec / 1000);
		if (def > data->t2die)
		{
			printf("%lu %d died\n", timeslap() - data->t_start, data->id);
			exit (0);
		}
		sem_post(data->lock_print);
		ft_usleep(200);
	}
	return (NULL);
}
