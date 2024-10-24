/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_simulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:16:01 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/24 19:30:46 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(t_data *data)
{
	int		i;
	int		status;

	i = 0;
	while (i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			if (status == 0)
				return ;
		}
		i++;
	}
}

int	check_full(t_data *data)
{
	int	meals;

	sem_wait(data->lock_death);
	meals = data->n_ate;
	if (data->max_meal < 0 || meals < data->max_meal)
	{
		sem_post(data->lock_death);
		return (0);
	}
	sem_post(data->lock_death);
	data->die = 1;
	sem_post(data->lock_print);
	return (1);
}

void	*check_die(void *data1)
{
	t_data			*data;
	size_t			delta_t;

	data = (t_data *)data1;
	while (1)
	{
		sem_wait(data->lock_print);
		delta_t = timeslap() - data->t_lastmeal;
		if (delta_t > data->t2die)
		{
			printf("%lu %d died\n", timeslap() - data->t_start, data->id);
			exit (0);
		}
		sem_post(data->lock_print);
		ft_usleep(200);
	}
	return (NULL);
}

void	simulate_philo(t_data *data, pid_t *philo)
{
	int		i;
	int		status;

	i = -1;
	data->t_start = timeslap();
	while (++i < data->n_philo)
	{
		philo[i] = fork();
		if (philo[i] == 0)
			doing(data, i + 1);
		if (philo[i] < 0)
			errors(ER_FORK, data, philo);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			if (status == 0)
				return ;
		}
	}
}
