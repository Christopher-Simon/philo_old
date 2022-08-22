/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:33:46 by christopher       #+#    #+#             */
/*   Updated: 2022/08/22 19:05:23 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	speak(t_philo philo, char *msg)
{
	suseconds_t elapsed;

	elapsed = get_time();
	pthread_mutex_lock(&philo.params->m_speak);
	printf("%ld %d %s\n", get_elapsed_time(philo.wait_time, elapsed), philo.id, msg);
	pthread_mutex_unlock(&philo.params->m_speak);
}

void	catch_fork(t_philo philo)
{
	pthread_mutex_lock(&philo.params->m_fork[philo.id]);
	pthread_mutex_lock(&philo.params->m_fork[philo.next_id]);
	speak(philo, EAT);
	usleep(10000);
	pthread_mutex_unlock(&philo.params->m_fork[philo.id]);
	pthread_mutex_unlock(&philo.params->m_fork[philo.next_id]);
	speak(philo, SLEEP);
}

void	*routine(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	philo.wait_time = get_time();
	catch_fork(philo);
	return (NULL);
}
