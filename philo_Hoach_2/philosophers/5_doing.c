/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_doing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:51:41 by nthoach           #+#    #+#             */
/*   Updated: 2024/10/23 14:37:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	if (print(philo, EATING))
	{
		UNLOCK(philo->left);
		UNLOCK(philo->right);
		return (1);
	}
	LOCK(&philo->data->lock_checktime);
	philo->t_lastmeal = timeslap();
	philo->n_ate++;
	UNLOCK(&philo->data->lock_checktime);
	ft_usleep(philo->data->t2eat);
	UNLOCK(philo->left);
	UNLOCK(philo->right);
	return (0);
}

int	thinking(t_philo *philo)
{
	ft_usleep(1);
	if (print(philo, THINKING))
		return (1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (print(philo, SLEEPING))
		return (1);
	ft_usleep(philo->data->t2sleep);
	return (0);
}

void	*doing(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	LOCK(&philo->data->lock_checktime);
	philo->t_lastmeal = philo->data->t_start;
	UNLOCK(&philo->data->lock_checktime);
	if (philo->id % 2)
		ft_usleep(2);
	while (1)
	{
		if (first_fork(philo))
			break ;
		if (second_fork(philo))
			break ;
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}
