/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:35:15 by nthoach           #+#    #+#             */
/*   Updated: 2024/09/02 22:57:18 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"


int	free_param(t_state *state, pthread_mutex_t *mutex, t_param *param)
{
	if (state)
		free(state);
	if (mutex)
		free(mutex);
	if (param)
		free(param);
	return (1);
}
				

int	agv2param(t_param *param, char **agv)
{
	if (check_agv(agv))
		return (exit_err());
	param->num_ate = 0;
	param->sim_time = in_time();
	param->num_philo = ft_atoi(agv[1]);
	param->time2die = ft_atoi(agv[2]);
	param->time2eat = ft_atoi(agv[3]);
	param->time2sleep = ft_atoi(agv[4]);
	if (param->num_philo <= 0 || param->time2die <=0
		|| param->time2eat <=0 || param->time2sleep <=0)
		return (1);
	if (agv[5])
	{
		param->num_eat = ft_atoi(agv[5]);
		if(param->num_eat <=0)
			return (1);
	}
	else
		param->num_eat = -1;
	return (0);
}

exit_err(void)
{
	printf("Error of parameters: num_phio time_die\
	time_eat time_sleep (num_eat)\n");
	return (1);
}

int	main(int agc, char **agv)
{
	int			i;
	t_param		*param;
	t_state		*state;
	pthread_t	*thread;

	if (agc != 5 && agc != 6)
		return (exit_err());
	param = (t_param *)malloc(sizeof(t_param));
	if (agv2param(param, agv))
		return (free_param(0, 0, state));
	state = (t_state *)malloc(sizeof(t_state) * param->num_philo);
	if (ini_param(state, param))
		return (1);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * param->num_philo);
	i = -1;
	while (++i < state->param->num_philo)
	{
		pthread_create(&thread[i], NULL, do_it, state + i);	
		usleep(100);
	}
	func(state, param);
	free(thread);
	return(0);
}
