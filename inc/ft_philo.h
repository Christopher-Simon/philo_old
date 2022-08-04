/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:52:20 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/04 14:44:12 by chsimon          ###   ########.fr       */
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

typedef struct s_philo
{
	int	fork;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	round;
	int	nb;
} t_philo;


//SECURED THREADING

int	sc_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine) (void *), void *arg);
int	sc_pthread_join(pthread_t thread, void **retval);

//SECURED TIME
int	sc_gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);


#endif