/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:51:41 by nthoach           #+#    #+#             */
/*   Updated: 2024/09/18 02:14:07 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "philo.h"

int	err(int	i, t_para *para)
{
	ft_putstr_fd("Invalid Arguments", 2);
	if (i == FL_PAR)
		free(para);
	return (i);
}

int	put_para(t_para *para, char **agv)
{
	para->n_phis = ft_atoi(agv[1]);
	para->living = 1;
	para->t_die = ft_atoi(agv[2]);
	para->t_eat = ft_atoi(agv[3]);
	para->t_sleep = ft_atoi(agv[4]);
	if (agv[5])
		para->n_meal = ft_atoi(agv[5]);
	else
		para->n_meal = -1;
	if ((para->n_meal <= 0 || agv[5])|| para->n_phis <= 0)
		return (FL_PAR);	
	return (OK);
}

int ini_phis(t_phis *phis, t_para *para, pthread_mutex_t *phi_lock)
{
	return (OK);
}
void run_philo(t_phis *phs, t_para *para, pthread_mutex_t *phi_lock)
{
	
}

int	main(int agc, char **agv)
{
	pthread_mutex_t	*phi_lock;
	t_phis			*phis;
	t_para			*para;
	
	if ((agc !=5 && agc != 6) || check_agv(agv))
		return (err(FL_ARG, NULL));
	para = (t_para *)malloc(sizeof(t_para));
	if (put_para(para, agv))
		return (err(FL_PAR, para));
	phis = (t_phis *)malloc((para->n_phis)*sizeof(t_phis));
	phi_lock = (pthread_mutex_t *)malloc(para->n_phis * sizeof(pthread_mutex_t));
	if (ini_phis(phis, para, phi_lock))
		return (1);
	run_philo(phis, para, phi_lock);
	free(para);
	free(phis);
	free(phi_lock);
	return (OK);
}

