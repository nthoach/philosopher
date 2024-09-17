/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 05:33:00 by nthoach           #+#    #+#             */
/*   Updated: 2024/09/18 02:10:53 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# define OK 0
# define FL_ARG 1
# define FL_PAR 2
# define TAKING 3
# define EATING 4
# define SLEEPING 5
# define THINKING 6

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_lock

typedef struct s_para
{
	int				n_phis;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meal;
	int				living;
	int				who_die;
	size_t			t;
	size_t			when_die;
	pthread_mutex_t	lock_die;
	pthread_mutex_t	lock_start;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_meal;
}				t_para;

typedef struct s_phis
{
	int				id;
	int				n_ate;
	int				is_dead;
	int				n_phi;
	int				ate;
	size_t			t_lastmeal;
	pthread_t		thread;
	pthread_mutex_t	*phi_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;	
}				t_phis;

void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char *str);
int		err(int state, t_para *para);


#endif
