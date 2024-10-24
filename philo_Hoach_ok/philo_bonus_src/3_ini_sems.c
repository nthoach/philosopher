/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ini_sems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:37 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/24 18:50:30 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_all(t_data *data, pid_t *philo)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		kill(philo[i], SIGKILL);
	sem_close(data->lock_print);
	sem_close(data->lock_forks);
	sem_close(data->lock_death);
	free_mem(data, philo);
}

int	ini_sems(t_data *data, pid_t *philo)
{
	sem_unlink("/sem_print");
	data->lock_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->lock_print == SEM_FAILED)
		return (errors(ER_SEM, data, philo));
	sem_unlink("/sem_forks");
	data->lock_forks = sem_open("/sem_forks", O_CREAT | O_EXCL, \
		0644, data->n_philo);
	if (data->lock_forks == SEM_FAILED)
	{
		sem_close(data->lock_print);
		return (errors(ER_SEM, data, philo));
	}
	sem_unlink("/sem_death");
	data->lock_death = sem_open("/sem_death", O_CREAT | O_EXCL, 0644, 1);
	if (data->lock_death == SEM_FAILED)
	{
		sem_close(data->lock_print);
		sem_close(data->lock_forks);
		return (errors(ER_SEM, data, philo));
	}
	return (OK);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = timeslap();
	while ((timeslap() - start) < milliseconds)
		usleep(200);
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
