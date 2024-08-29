/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:36:35 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/08 19:59:31 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	errors(int state, t_data *data)
{
	ft_putstr_fd("INVALID ARGS", 2);
	if (state == INVALI_VAL)
		free (data);
	return (state);
}

int	val_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	j = i;
	while (str[i])
		i++;
	return (i - j);
}

int	is_intiger(char **av)
{
	int	i;
	int	len;

	i = 1;
	while (av[i])
	{
		len = val_len(av[i]);
		if (len > 10)
			return (1);
		if (len == 10)
		{
			if (ft_atoi(av[i]) > 2147483647)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (j == 0 && av[i][j] == '+')
			{
				j++;
				continue ;
			}
			if ((!(av[i][j] >= '0' && av[i][j] <= '9')))
				return (1);
			j++;
		}
		i++;
	}
	return (is_intiger(av));
}
