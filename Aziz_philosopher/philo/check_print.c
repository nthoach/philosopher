/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:58:13 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/08 17:59:29 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	LOCK(&philo->data->lock_die);
	if (philo->data->die == 1)
	{
		UNLOCK(&philo->data->lock_die);
		return (1);
	}
	UNLOCK(&philo->data->lock_die);
	return (0);
}

int	print(t_philo *philo, int flag)
{
	if (is_dead(philo))
		return (1);
	LOCK(&philo->data->lock_print);
	if (flag == TAKE)
	{
		printf("%lu %d has taken a fork\n", \
			get_time() - philo->data->t, philo->id);
	}
	else if (flag == EATING)
	{
		printf("%lu %d is eating\n", get_time() - philo->data->t, philo->id);
	}
	else if (flag == SLEEPING)
	{
		printf("%lu %d is sleeping\n", get_time() - philo->data->t, philo->id);
	}
	else if (flag == THINKING)
	{
		printf("%lu %d is thinking\n", get_time() - philo->data->t, philo->id);
	}
	UNLOCK(&philo->data->lock_print);
	return (0);
}
