/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_check_agv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:51:41 by nthoach           #+#    #+#             */
/*   Updated: 2024/10/22 19:28:35 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	size_t	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return ((result * sign));
}

int	ft_strlen(char *str)
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

int	is_int(char **agv)
{
	int	i;
	int	len;

	i = 1;
	while (agv[i])
	{
		len = ft_strlen(agv[i]);
		if (len > 10)
			return (1);
		if (len == 10)
		{
			if (ft_atoi(agv[i]) > INT8_MAX)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_agv(char **agv)
{
	int	i;
	int	j;

	i = 1;
	while (agv[i])
	{
		j = 0;
		while (agv[i][j])
		{
			if (j == 0 && agv[i][j] == '+')
			{
				j++;
				continue ;
			}
			if ((agv[i][j] < '0' || agv[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (is_int(agv));
}
