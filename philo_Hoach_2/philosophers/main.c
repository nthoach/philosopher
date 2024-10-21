/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:37 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/21 17:26:11 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*doing(void *ptr)
{
	t_philo	*philo;

	if (!ptr)
		return (0);
	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(100);
	philo->t_lastmeal = timeslap();
	while (1)
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		print(philo, runtime(philo), "has taken his left fork");
		pthread_mutex_lock(&philo->forks[philo->id % philo->data->n_philo]);
		print(philo, runtime(philo), "has taken his right fork");
		print(philo, runtime(philo), "is eating");
		philo->n_ate++;
		if (philo->n_ate == philo->data->max_meal)
			philo->data->n_full++;
		usleep(philo->data->t_eat * 1000);
		philo->t_lastmeal = timeslap();
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->forks[philo->id % philo->data->n_philo]);
		print(philo, runtime(philo), "is sleeping");
		usleep(philo->data->t_sleep * 1000);
		print(philo, runtime(philo), "is thinking");
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	return (0);
}

void	simulate(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].data->n_full == philo[i].data->n_philo)
		{
			pthread_mutex_lock(&philo[i].data->stop_mutex);
			philo[i].data->stop = 1;
			pthread_mutex_unlock(&philo[i].data->stop_mutex);
			dest_mutex(philo);
			free_all(philo, philo->forks, data);
			return ;
		}
		if (timeslap() - philo[i].t_lastmeal
			> (size_t)data->t_die)
		{
			usleep(1000);
			pthread_mutex_lock(philo->print);
			printf("[%lums]	%d died\n", runtime(philo), philo->id);
			pthread_mutex_lock(&philo[i].data->stop_mutex);
			philo[i].data->stop = 1;
			pthread_mutex_unlock(&philo[i].data->stop_mutex);
			dest_mutex(philo);
			free_all(philo, philo->forks, data);
			return ;
		}
		i = (i + 1) % data->n_philo;
		usleep(1000);
	}
}

int	main(int agc, char **agv)
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				i;

	if (agc < 5 || agc > 6 || check_agv(agv))
		return (err(ER_ARG, NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data || agc_data(agv, data))
		return (err(ER_DATA, data));
	philo = (t_philo *)malloc((data->n_philo) * sizeof(t_philo));
	forks = (pthread_mutex_t *)malloc((data->n_philo) * \
			sizeof(pthread_mutex_t));
	if (set_philo(philo, data, forks))
		return (err(ER_DATA, data));
	i = 0;
	while (i < data->n_philo)
	{
		pthread_create(&threads[i], NULL, doing, philo + i);
		usleep(1000);
		i++;
	}
	simulate(philo, data);
	free(threads);
	return (OK);
}
