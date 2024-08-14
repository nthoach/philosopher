/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:34:42 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/12 16:07:49 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *mutex)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].t_die = data->t_die;
		philos[i].t_eat = data->t_eat;
		philos[i].t_sleap = data->t_sleap;
		philos[i].nb_philo = data->n_philo;
		philos[i].last_meal = 0;
		philos[i].eated = 0;
		philos[i].meals_eaten = 0;
		philos[i].is_dead = 0;
		philos[i].own_fork = &mutex[i];
		philos[i].left_fork = &mutex[(i + 1) % data->n_philo];
	}
}

int	check_failed(t_philo *philos, t_data *data, pthread_mutex_t *mutex)
{
	if ((philos != NULL && data != NULL && mutex != NULL))
		return (0);
	if (philos != NULL)
		free(philos);
	if (data != NULL)
		free(data);
	if (mutex != NULL)
		free(mutex);
	return (1);
}

int	destroy(t_philo *philos, t_data *data, pthread_mutex_t *mutex, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&mutex[j]);
		j++;
	}
	free(philos);
	free(data);
	free(mutex);
	return (1);
}

int	init(t_philo *philos, t_data *data, pthread_mutex_t *mutex)
{
	int	i;
	int	count;

	if (check_failed(philos, data, mutex) == 1)
		return (1);
	i = -1;
	count = 0;
	while (++i < data->n_philo && count == 0)
		count += pthread_mutex_init(&mutex[i], NULL);
	if (count != 0)
		return (destroy(philos, data, mutex, i));
	if (mutex_init(philos, data, mutex))
	{
		free(philos);
		free(data);
		free(mutex);
		return (1);
	}
	init_philos(philos, data, mutex);
	return (0);
}

int	fill_data(t_data *data, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->die = 0;
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleap = ft_atoi(av[4]);
	if (av[5])
		data->meals = ft_atoi(av[5]);
	else
		data->meals = -1;
	if (data->n_philo <= 0 || (av[5] && data->meals <= 0))
		return (1);
	return (0);
}
