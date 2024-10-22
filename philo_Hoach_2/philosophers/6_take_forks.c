/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_take_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:06:12 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/22 19:54:13 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left(t_philo *philo)
{
	if (philo->data->n_philo == 1)
		return (1);
	LOCK(philo->left);
	if (print(philo, TAKING))
	{
		UNLOCK(philo->left);
		return (1);
	}
	return (0);
}

int	take_right(t_philo *philo)
{
	LOCK(philo->right);
	if (print(philo, TAKING))
	{
		UNLOCK(philo->right);
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
		if (take_right(philo))
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
			UNLOCK(philo->right);
			return (1);
		}
	}
	else if (!(philo->id % 2))
	{
		if (take_right(philo))
		{
			UNLOCK(philo->left);
			return (1);
		}
	}
	return (0);
}
