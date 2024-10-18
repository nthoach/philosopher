/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:37 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/18 18:32:16 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*doing(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(10);
	philo->t_lastmeal = timeslap();
	while (1)
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		print(philo, runtime(philo), "has taken a fork");
		pthread_mutex_lock(&philo->forks[philo->id % philo->data->n_philo]);
		print(philo, runtime(philo), "has taken a fork");
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
			dest_mutex(philo);
			free_all(philo, philo->forks, data);
			return ;
		}
		if (timeslap() - philo[i].t_lastmeal
			> (size_t)data->t_die)
		{
			usleep(100);
			pthread_mutex_lock(philo->print);
			printf("%lums	%d died", runtime(philo), philo->id);
			dest_mutex(philo);
			free_all(philo, philo->forks, data);
			return ;
		}
		i = (i + 1) % data->n_philo;
		usleep(500);
	}
}

int	main(int agc, char **agv)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	*threads;
	int			i;

	if (agc < 5 || agc > 6 || check_agv(agv))
		return (err(ER_ARG, data));
	data = (t_data *)malloc(sizeof(t_data));
	if (agc_data(agv, data))
		return (1);
	philo = (t_philo *)malloc((data->n_philo) * sizeof(t_philo));
	if (set_philo(philo, data))
		return (1);
	threads = (pthread_t *)malloc(data->n_philo * sizeof(pthread_t));
	i = 0;
	while (i < data->n_philo)
	{
		pthread_create(&threads[i], NULL, doing, philo + i);
		usleep(100);
		i++;
	}
	simulate(philo, data);
	free(threads);
	return (OK);
}
