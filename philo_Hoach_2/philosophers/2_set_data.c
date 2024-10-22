/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_set_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:22:59 by honguyen          #+#    #+#             */
/*   Updated: 2024/10/22 20:04:01 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	errors(int err_code, t_data *data, t_philo *philo, \
	pthread_mutex_t *forks)
{
	if (data)
		free(data);
	if (!philo)
		free(philo);
	if (!forks)
		free(forks);
	if (err_code == ER_ARG)
		ft_putstr_fd("Ivalid arguments, i.e., ./philo 5 20 5 5 5 \n", 2);
	else if (err_code == ER_DATA)
		ft_putstr_fd("Error in memory allication \n", 2);
	else
		ft_putstr_fd("Unknow Errors \n", 2);
	return (err_code);
}

int	set_data(char **agv, t_data *data)
{
	data->n_philo = ft_atoi(agv[1]);
	data->t2die = ft_atoi(agv[2]);
	data->t2eat = ft_atoi(agv[3]);
	data->t2sleep = ft_atoi(agv[4]);
	if (data->n_philo <= 0 || data->t2die <= 0
		|| data->t2eat <= 0 || data->t2sleep <= 0)
		return (errors(ER_ARG, data, NULL, NULL));
	if (agv[5])
	{
		data->max_meal = ft_atoi(agv[5]);
		if (data->max_meal <= 0)
			return (errors(ER_ARG, data, NULL, NULL));
	}
	else
		data->max_meal = -1;
	data->die = -1;
	data->full = 0;
	return (OK);
}
