/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:52:20 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/24 18:16:09 by chsimon          ###   ########.fr       */
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

# define DB_PARAMS	1
# define DB_PHILO	1
# define DB_PRMS_TH	1

typedef struct s_params
{
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	m_speak;
	int				fork;
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
int			destroy_philo(t_philo *philo);
void		print_philo(t_philo *philo);

//INIT DB
void	print_params(t_params *params, t_philo philo);
void	print_philo(t_philo *philo);

//INIT MUTEX
int	init_mutex(t_params *params);
int	end_mutex(pthread_mutex_t *mutex, int nb);

//TIME
time_t		get_time();
time_t		get_elapsed_time(suseconds_t time1, suseconds_t time2);

//THREADATOR
int	threadator(t_philo *philo, t_params *params);

//ROUTINE
void	*routine(void *arg);
int		saint_chro_start(t_philo philo);
int		is_dead(t_philo philo);

#endif