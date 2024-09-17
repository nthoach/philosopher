/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_agv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:51:41 by nthoach           #+#    #+#             */
/*   Updated: 2024/09/18 01:47:26 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int	is_integer(char **agv)
{
	int	i;
	int	len;

	i = 1;
	while (agv[i])
	{
		len = ft_strlen(agv[i]);
		if (len > 10)
			return (FL_ARG);
		if (len == 10)
		{
			if (ft_atoi(agv[i]) > INT8_MAX)
				return (FL_ARG);
		}
		i++;
	}
	return (OK);
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
			if (j == 0 && agv[i][j] == "+")
			{
				j++;
				continue ;
			}
			if ((agv[i][j] < 0 || agv[i][j] > 9))
				return (FL_ARG);
			j++;
		}
		i++;
	}	
	return (is_integer(agv));
}