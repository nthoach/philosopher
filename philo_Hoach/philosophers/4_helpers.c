/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:16:01 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/19 09:50:17 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	runtime(t_philo *philo)
{
	return (timeslap() - philo->data->t_start);
}

void	print(t_philo *philo, size_t time, char *is_doing)
{
	pthread_mutex_lock(philo->print);
	printf("[%lums]	%d %s\n", time, philo->id, is_doing);
	pthread_mutex_unlock(philo->print);
}

void	dest_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
		pthread_mutex_destroy(&philo->forks[i++]);
}
