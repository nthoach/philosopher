/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 05:33:00 by nthoach           #+#    #+#             */
/*   Updated: 2024/10/24 12:46:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
//# include <string.h>
# include <stdio.h>
# include <stdbool.h>

# define OK 0
# define NOK 1
# define ER_ARG 2
# define ER_DATA 3
# define ER_MUTEX 3
# define TAKING 4
# define EATING 5
# define SLEEPING 6
# define THINKING 7

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_unlock

// [n_philo]number of philospher
// [t2die]time to die [ms],
// [t2eat] time to eat [ms]
// [t2sleep] time to sleep [ms], [n_meal]number of meals to be eaten
// [max_meal ] number of meals to stop
// [n_full] number of full philosoher 
// [t_start] instant of start silumation
// [t_death] instant of a philosopher dead
// [die] status when one phislophe has died
// [full] status when all philospher has eaten max_meals

typedef struct s_data
{
	int					n_philo;
	size_t				t2die;
	int					t2eat;
	int					t2sleep;
	int					max_meal;
	size_t				t_start;
	size_t				t_death;
	int					die;
	pthread_mutex_t		lock_print;
	pthread_mutex_t		lock_checktime;
	pthread_mutex_t		lock_checkdie;
	pthread_mutex_t		lock_checkfull;
}				t_data;

// [id] id of philospher
// [n_ate] number of ate meals
// [t_lastmeal] instant of last meal ate
// [*data] pointer to data structure of program
// [*forks] mutex lockers for forks
// [*print] mutex lockers for print devices

typedef struct s_philo
{
	bool				death;
	int					id;
	int					n_ate;
	size_t				t_lastmeal;
	pthread_t			thread;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	t_data				*data;
}				t_philo;

//1_check arguments
size_t	ft_atoi(const char *str);
int		ft_strlen(char *str);
int		is_int(char **agv);
int		check_agv(char **agv);

//2_set data
void	ft_putstr_fd(char *str, int fd);
int		errors(int err_code, t_data *data, t_philo *philo, \
		pthread_mutex_t *forks);
int		set_data(char **agv, t_data *data);

//3_set philo
int		destroy_all(t_data *data, t_philo *philo, \
				pthread_mutex_t *forks, int i);
int		ini_locks(t_data *data);
void	init_philo(t_data *data, t_philo *philo, pthread_mutex_t *forks);
int		ini_lock_philo(t_data *data, t_philo *philo, pthread_mutex_t *forks);

//4_simulate
int		check_full(t_data *data, t_philo *philo);
void	check_all(t_data *data, t_philo *philo);
void	destroy_locks(t_data *data, pthread_mutex_t *forks);
void	simulate_philo(t_data *data, t_philo *philo, pthread_mutex_t *forks);

//5_doing
int		eating(t_philo *philo);
int		thinking(t_philo *philo);
int		sleeping(t_philo *philo);
void	*doing(void *ptr);

//6_take forks
int		take_left(t_philo *philo);
int		take_right(t_philo *philo);
int		first_fork(t_philo *philo);
int		second_fork(t_philo *philo);

//7_printing
int		check_dead(t_philo *philo);
int		print(t_philo *philo, int flag);
int		ft_usleep(size_t milliseconds);
size_t	timeslap(void);
void	free_mem(t_data *data, t_philo *philo, pthread_mutex_t *forks);

#endif
