/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 05:33:00 by nthoach           #+#    #+#             */
/*   Updated: 2024/10/24 18:29:32 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdint.h>
# include <fcntl.h>

# define OK 0
# define NOK 1
# define ER_ARG 2
# define ER_DATA 3
# define ER_SEM 4
# define ER_FORK 5

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
	int					n_ate;
	int					id;
	size_t				t_start;
	size_t				t_lastmeal;
	size_t				t_death;
	int					die;
	sem_t				*lock_print;
	sem_t				*lock_forks;
	sem_t				*lock_death;
}				t_data;

//1_check arguments
size_t	ft_atoi(const char *str);
int		ft_strlen(char *str);
int		is_int(char **agv);
int		check_agv(char **agv);

//2_set data
void	ft_putstr_fd(char *str, int fd);
int		errors(int err_code, t_data *data, pid_t *philo);
int		set_data(char **agv, t_data *data);

//3_ini_sems
void	close_all(t_data *data, pid_t *philo);
int		ini_sems(t_data *data, pid_t *philo);
int		ft_usleep(size_t milliseconds);
size_t	timeslap(void);

//4_simulate
void	simulate_philo(t_data *data, pid_t *philo);
int		check_full(t_data *data);
void	*check_die(void *data1);
int		ft_usleep(size_t milliseconds);

//5_doing
void	taking_forks(t_data	*data, int id);
void	eating(t_data	*data, int id);
void	sleeping(t_data	*data, int id);
void	thinking(t_data	*data, int id);
void	doing(t_data	*data, int id);

// main
void	free_mem(t_data *data, pid_t *philo);
void	waiting(t_data *data);

#endif
