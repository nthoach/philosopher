/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agc_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:22:59 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/18 17:52:12 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	err(int err_code, t_data *data)
{
	if (data)
		free(data);
	if (err_code == ER_ARG)
		ft_putstr_fd("Invalid arguments, i.e., ./philo 5 20 5 5 5", 2);
	if (err_code == ER_DATA)
		ft_putstr_fd("Error in data initialization", 2);
	return (err_code);
}

int	agc_data(char **agv, t_data *data)
{
	if (!data)
		return (err(ER_DATA, NULL));
	data->n_full = 0;
	data->t_start = timeslap();
	data->n_philo = ft_atoi(agv[1]);
	data->t_die = ft_atoi(agv[2]);
	data->t_eat = ft_atoi(agv[3]);
	data->t_sleep = ft_atoi(agv[4]);
	if (data->n_philo <= 0 || data->t_die <= 0
		|| data->t_eat <= 0 || data->t_sleep <= 0)
		return (err(ER_ARG, data));
	if (agv[5])
	{
		data->max_meal = ft_atoi(agv[5]);
		if (data->max_meal <= 0)
			return (err(ER_ARG, data));
	}
	else
		data->max_meal = -1;
	return (OK);
}
