/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:08:16 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/15 18:48:10 by afadouac         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>

# define INVALI_ARGS 1
# define INVALI_VAL 2
# define FORK_FAILED 3

typedef struct s_data
{
	sem_t			*lock_print;
	sem_t			*forks;
	sem_t			*death;
	int				n_philo;
	int				id;
	int				meals_eated;
	struct timeval	last_meal;
	size_t			t;
	int				die;
	size_t			t_die;
	int				t_eat;
	int				t_sleap;
	int				meals;
}				t_data;

int		finish_meals(t_data *data);
void	*is_dead(void *data1);
int		errors(int state, t_data *data);
int		check_arg(char **av);
int		fill_data(t_data *data, char **av);
void	close_sem(t_data *data, pid_t *pid);
void	init_sems2(t_data *data, pid_t *pid);
void	init_sems(t_data *data, pid_t *pid);
void	ft_putstr_fd(char *str, int fd);
size_t	ft_atoi(const char *str);
size_t	get_time(void);
int		ft_usleep(size_t milliseconds);
void	routine(t_data	*data, int id);
#endif