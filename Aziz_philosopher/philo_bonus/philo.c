/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:08:04 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/15 18:47:42 by afadouac         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	int				i;
	pid_t			*pid;
	t_data			*data;

	i = 0;
	if ((ac != 6 && ac != 5) || check_arg(av))
		return (errors(INVALI_ARGS, NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (fill_data(data, av))
		return (errors(INVALI_VAL, data));
	pid = (pid_t *)malloc(sizeof(pid_t) * data->n_philo);
	init_sems(data, pid);
	data->t = get_time();
	while (i < data->n_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			routine(data, i + 1);
		if (pid[i] < 0)
			return (free(pid), free(data), FORK_FAILED);
		i++;
	}
	waiting(data);
	close_sem(data, pid);
}
