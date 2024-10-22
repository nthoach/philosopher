/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_simulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:16:01 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/22 19:57:59 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_data *data, t_philo *philo)
{
	int	i;

	if (data->max_meal == -1)
		return (0);
	i = 0;
	while (i < data->n_philo)
	{
		if (philo[i].n_ate < data->max_meal)
			return (0);
		i++;
	}
	return (1);
}

void	check_all(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		LOCK(&data->lock_checktime);
		LOCK(&data->lock_checkdie);
		if ((philo[i].t_lastmeal && \
			(timeslap() - philo[i].t_lastmeal > data->t2die)) || \
				check_full(data, philo))
		{
			data->die = i;
			UNLOCK(&data->lock_checktime);
			UNLOCK(&data->lock_checkdie);
			break ;
		}
		i++;
		i = i % data->n_philo;
		UNLOCK(&data->lock_checkdie);
		UNLOCK(&data->lock_checkfull);
	}
	if (check_full(data, philo))
		data->die = -1;
	data->t_death = timeslap();
}

void	destroy_locks(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i++ < data->n_philo)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&data->lock_print);
	pthread_mutex_destroy(&data->lock_checktime);
	pthread_mutex_destroy(&data->lock_checkdie);
	pthread_mutex_destroy(&data->lock_checkfull);
}

void	simulate_philo(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	int			i;

	i = 0;
	data->t_start = timeslap();
	while (i < data->n_philo)
	{
		pthread_create(&philo[i].thread, NULL, doing, &philo[i]);
		i++;
	}
	check_all(data, philo);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (data->die == -1)
		return ;
	printf("%lu %d died\n", \
			data->t_death - data->t_start, data->die);
	destroy_locks(data, forks);
}
