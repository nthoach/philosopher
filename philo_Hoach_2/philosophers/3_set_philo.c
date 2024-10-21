/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_set_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:37 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/21 17:42:57 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(pthread_mutex_t *forks, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&forks[i]);
		j++;
	}
}

int	free_all(t_philo *philo, pthread_mutex_t *forks, t_data *data)
{
	if (forks)
		free(forks);
	if (philo)
		free(philo);
	if (data)
		free(data);
	return (1);
}

void	ini_philo(t_philo *philo, t_data *data,
	pthread_mutex_t *forks, pthread_mutex_t *print)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philo[i].n_ate = 0;
		philo[i].id = i + 1;
		philo[i].forks = forks;
		philo[i].data = data;
		i++;
	}
}

int	set_philo(t_philo *philo, t_data *data, pthread_mutex_t *forks)
{
	int				i;
	int				error;

	if (!forks || !philo)
		return (free_all(philo, forks, data));
	i = 0;
	error = 0;
	while (i++ < data->n_philo && error == 0)
		error += pthread_mutex_init(&forks[i], NULL);
	if (error)
	{
		destroy_forks(forks, i);
		return (free_all(philo, forks, data));
	}
	ini_philo(philo, data, forks, &print);
	return (OK);
}
