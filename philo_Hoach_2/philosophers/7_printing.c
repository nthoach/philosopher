/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_printing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:13:19 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/23 14:53:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	LOCK(&philo->data->lock_checkdie);
	if (philo->data->die != -1)
	{
		UNLOCK(&philo->data->lock_checkdie);
		return (1);
	}
	UNLOCK(&philo->data->lock_checkdie);
	return (0);
}

int	print(t_philo *philo, int flag)
{
	if (check_dead(philo))
		return (1);
	LOCK(&philo->data->lock_print);
	if (flag == TAKING)
	{
		printf("%lu %d has taken a fork\n", \
			timeslap() - philo->data->t_start, philo->id);
	}
	else if (flag == EATING)
	{
		printf("%lu %d is eating\n", \
			timeslap() - philo->data->t_start, philo->id);
	}
	else if (flag == SLEEPING)
	{
		printf("%lu %d is sleeping\n", \
			timeslap() - philo->data->t_start, philo->id);
	}
	else if (flag == THINKING)
	{
		printf("%lu %d is thinking\n", \
			timeslap() - philo->data->t_start, philo->id);
	}
	UNLOCK(&philo->data->lock_print);
	return (0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = timeslap();
	while ((timeslap() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	timeslap(void)
{
	struct timeval	time;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	return (l);
}
