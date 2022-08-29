/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:52:20 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/29 15:31:03 by christopher      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include "ft_my_lib.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

# define TAKE	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define DIE	"died"
# define THINK	"is thinking"

# define DISPO		0
# define UNDISPO	1

//DEFINE DEBUG

# define DB_PARAMS	0
# define DB_PHILO	0
# define DB_PRMS_TH	0
# define DB_HADES	0

# define PAIR		2 == 0
# define IMPAIR		2 == 1

typedef struct s_params
{
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	*m_cycle;
	int				*used;
	pthread_mutex_t	m_speak;
	int				fork;
	int				death;
	int				stop;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_death;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	time_t			init_time;
} t_params;

typedef struct s_philo
{
	int			id;
	int			fork;
	int			next_fork;
	t_params	*params;
	// time_t		wait_time;
	time_t		init_time;
	time_t		cycle_time;
	// time_t		restored_time;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			round;
	int			impair;
} t_philo;

//SECURED THREADING

int			sc_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine) (void *), void *arg);
int			sc_pthread_join(pthread_t thread, void **retval);

int			sc_pthread_mutex_init(pthread_mutex_t *restrict mutex, 
		const pthread_mutexattr_t *restrict attr);
int			sc_pthread_mutex_destroy(pthread_mutex_t *restrict mutex);

//SECURED TIME
int			sc_gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);

//INIT
t_params	*get_params(char **argv);
int			init_struct_philo(char **argv,t_philo **philo);
int			destroy_params(t_params *params);
int			destroy_philo(t_philo *philo);

//INIT DB
void	print_params(t_params *params, t_philo philo);
void	print_all_philo(t_philo *philo);
void	print_philo(t_philo philo);

//INIT MUTEX
int		init_mutex(t_params *params);
int		end_mutex(pthread_mutex_t *mutex, int nb);

//TIME
time_t		get_time();
time_t		get_elapsed_time(suseconds_t time1, suseconds_t time2);

//THREADATOR
int		threadator(t_philo *philo, t_params *params);
int		create_shinigami(t_philo *philo, pthread_t *th_philo, int nb_philo);

//ROUTINE
void	*routine(void *arg);
int		speak(t_philo philo, char *msg);
int		saint_chro_start(t_philo philo);
int		is_dead(t_philo philo);
int		is_one_dead(t_philo philo);
int		update_cycle(t_philo *philo, t_params *params);
int		net_usleep(time_t time_to_wait);

void	*shinigami(void *arg);

int		is_gonna_die(time_t wait_time, time_t death_time);
time_t	time_to_wait(time_t wait_time, time_t death_time);

#endif