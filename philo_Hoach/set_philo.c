/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:37 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/18 17:15:44 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_philo *philo, pthread_mutex_t *forks, t_data *data)
{
	if (philo)
		free(philo);
	if (forks)
		free(forks);
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
		philo[i].print = print;
		philo[i].data = data;
		i++;
	}
}

int	set_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!forks || !philo)
		return (free_all(philo, forks, data));
	i = 0;
	while (i < data->n_philo)
		if (pthread_mutex_init(&forks[i++], 0))
			return (free_all(philo, forks, data));
	if (pthread_mutex_init(&print, 0))
		return (free_all(philo, forks, data));
	ini_philo(philo, data, forks, &print);
	return (OK);
}