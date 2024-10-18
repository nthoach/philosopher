/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 05:33:00 by nthoach           #+#    #+#             */
/*   Updated: 2024/10/18 18:08:53 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# define OK 0
# define ER_ARG 1
# define ER_DATA 2
# define TAKING 3
# define EATING 4
# define SLEEPING 5
# define THINKING 6

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_lock

//[n_philo]number of philospher, [t_die]time to die [ms],
// [t_eat] time to eat [ms]
// [t_sleep] time to sleep [ms], [n_meal]number of meals to be eaten
// [n_full ]number of philospher to be full
// [t_start] starting instant of simulation

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meal;
	int				n_full;
	size_t			t_start;
}				t_data;

// [id] id of philospher
// [n_ate] number of ate meals
// [t_lastmeal] instant of last meal ate
// [*data] pointer to data structure of program
// [*fork_locker] mutex to lock the fork
// [*print_locker] mutex to lock the print

typedef struct s_philo
{
	int					id;
	int					n_ate;
	size_t				t_lastmeal;
	t_data				*data;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;	
}				t_philo;

//main

int		check_agv(char **agv);
int		is_integer(char **agv);
int		ft_strlen(char *str);
size_t	ft_atoi(const char *str);

int		agc_data(char **agv, t_data *data);
int		err(int err_code, t_data *data);

int		set_philo(t_philo *philo, t_data *data);
void	ini_philo(t_philo *philo, t_data *data, pthread_mutex_t *forks, pthread_mutex_t *print);
int		free_all(t_philo *philo, pthread_mutex_t *forks, t_data *data);

void	*doing(void *p);
size_t	timeslap(void);
void	print(t_philo *philo, size_t time, char *is_doing);
size_t	runtime(t_philo *philo);

void	simulate(t_philo *philo, t_data	*data);	
void	dest_mutex(t_philo *philo);
#endif
