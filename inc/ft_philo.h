/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:52:20 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/01 11:10:18 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

//SECURED THREADING

int	sc_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine) (void *), void *arg);
int	sc_pthread_join(pthread_t thread, void **retval);

//SECURED TIME
int	sc_gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);


#endif