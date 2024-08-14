/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:33:02 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/12 16:06:00 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define SUCSESS 0
# define INVALI_ARGS 1
# define INVALI_VAL 2
# define TAKE 3
# define EATING 4
# define SLEEPING 5
# define THINKING 6

# define LOCK pthread_mutex_lock
# define UNLOCK pthread_mutex_unlock

typedef struct s_data
{
	int				n_philo;
	size_t			t;
	int				die;
	int				die_index;
	size_t			death_time;
	size_t			t_die;
	int				t_eat;
	int				t_sleap;
	int				meals;
	pthread_mutex_t	lock_die;
	pthread_mutex_t	lock_time_start;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_last_meal;
}				t_data;

typedef struct s_philo
{
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*mutex;
	size_t			t_die;
	int				t_eat;
	int				t_sleap;
	int				meals;
	int				nb_philo;
	int				is_dead;
	int				id;
	int				eated;
	int				meals_eaten;
	size_t			last_meal;
	int				start_time;
	pthread_mutex_t	*own_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char *str);
int		errors(int state, t_data *data);
int		check_arg(char **av);
size_t	ft_atoi(const char *str);
int		init(t_philo *philos, t_data *data, pthread_mutex_t *mutex);
int		fill_data(t_data *data, char **av);
size_t	get_time(void);
int		ft_usleep(size_t milliseconds);
void	*routine(void *tphilo);
int		eating(t_philo *philos);
int		sleeping(t_philo *philos);
int		thinking(t_philo *philos);
void	monitor(t_philo *philo, t_data *data);
int		take_left(t_philo *philo);
int		take_own(t_philo *philo);
int		first_fork(t_philo *philo);
int		second_fork(t_philo *philo);
int		print(t_philo *philo, int flag);
int		is_dead(t_philo *philo);
int		mutex_init(t_philo *philos, t_data *data, pthread_mutex_t *mutex);
int		destroy(t_philo *philos, t_data *data, pthread_mutex_t *mutex, int i);
#endif
