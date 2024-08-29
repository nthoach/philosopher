/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sems.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:28:51 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/15 18:46:22 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_sem(t_data *data, pid_t *pid)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	sem_close(data->lock_print);
	sem_close(data->forks);
	free (data);
	free (pid);
}

void	init_sems2(t_data *data, pid_t *pid)
{
	sem_unlink("/forks_sem");
	data->forks = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644, data->n_philo);
	if (data->forks == SEM_FAILED)
	{
		sem_close(data->lock_print);
		free(pid);
		free(data);
		exit (8);
	}
}

void	init_sems(t_data *data, pid_t *pid)
{
	if (pid == NULL)
	{
		free (data);
		exit (5);
	}
	sem_unlink("/print_sem");
	data->lock_print = sem_open("/print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->lock_print == SEM_FAILED)
	{
		free(pid);
		free(data);
		exit (6);
	}
	init_sems2(data, pid);
}
