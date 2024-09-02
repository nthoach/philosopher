/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:35:19 by nthoach           #+#    #+#             */
/*   Updated: 2024/09/02 22:09:27 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef	PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_param
{
	int				num_philo;
	int				time2eat;
	int				time2sleep;
	int				time2die;
	int				num_eat;
	int				num_ate;
	unsigned long	sim_time;
} t_param;

typedef struct s_state
{
	unsigned long	last_meal;
	int				ate;
	int				id;
	t_param			*param;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
} t_state;

int				ft_atoi(char *str);
int				exit_err(void);
int				check_agv(char **agv);
int				agv2param(t_param *param, char **agv);
void			put_param(t_state *state, t_param *vars,
				pthread_mutex_t *mutex, pthread_mutex_t print);
int				ini_param(t_state *state, t_param *param);
int				free_param(t_state *state, pthread_mutex_t *mutex,
				t_param *param);
void			destroy_mutex();
unsigned long	int_time(void);
unsigned long	real_time(t_state *state);
void			print_state(t_state *state, unsigned long time, char *doing);
void			*do_it(void *p);
void			func(t_state *state, t_param *param);
				
#endif