/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:37 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/22 20:04:18 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int agc, char **agv)
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (agc < 5 || agc > 6 || check_agv(agv))
		return (errors(ER_ARG, NULL, NULL, NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (errors(ER_DATA, NULL, NULL, NULL));
	if (set_data(agv, data))
		return (NOK);
	philo = ((t_philo *)malloc((data->n_philo) * sizeof(t_philo)));
	forks = (pthread_mutex_t *)malloc(data->n_philo * sizeof(pthread_mutex_t));
	if (!philo || !forks)
		return (errors(ER_DATA, data, philo, forks));
	if (ini_lock_philo(data, philo, forks))
		return (NOK);
	simulate_philo(data, philo, forks);
	free(data);
	free(philo);
	free(forks);
	return (OK);
}
