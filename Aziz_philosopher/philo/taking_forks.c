/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:36:36 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/12 18:07:05 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left(t_philo *philo)
{
	if (philo->nb_philo == 1)
		return (1);
	LOCK(philo->left_fork);
	if (print(philo, TAKE))
	{
		UNLOCK(philo->left_fork);
		return (1);
	}
	return (0);
}

int	take_own(t_philo *philo)
{
	LOCK(philo->own_fork);
	if (print(philo, TAKE))
	{
		UNLOCK(philo->own_fork);
		return (1);
	}
	return (0);
}

int	first_fork(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		if (take_left(philo))
			return (1);
	}
	else if ((philo->id % 2))
	{
		if (take_own(philo))
			return (1);
	}
	return (0);
}

int	second_fork(t_philo *philo)
{
	if ((philo->id % 2))
	{
		if (take_left(philo))
		{
			UNLOCK(philo->own_fork);
			return (1);
		}
	}
	else if (!(philo->id % 2))
	{
		if (take_own(philo))
		{
			UNLOCK(philo->left_fork);
			return (1);
		}
	}
	return (0);
}
