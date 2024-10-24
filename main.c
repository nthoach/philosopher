/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:37 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/24 15:44:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mem(t_data *data, pid_t *philo)
{
	if (data)
		free(data);
	if (philo)
		free(philo);
}

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

int	main(int agc, char **agv)
{
	t_data				*data;
	pid_t				*philo;

	if (agc < 5 || agc > 6 || check_agv(agv))
		return (errors(ER_ARG, NULL, NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (errors(ER_DATA, data, NULL));
	if (set_data(agv, data))
		return (NOK);
	philo = ((pid_t *)malloc((data->n_philo) * sizeof(pid_t)));
	if (!philo)
		return (errors(ER_DATA, data, philo));
	if(ini_sems(data, philo))
		return (NOK);
	simulate_philo(data, philo);
	close_all(data, philo);
	return (OK);
}
