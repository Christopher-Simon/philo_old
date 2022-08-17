/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:33:46 by christopher       #+#    #+#             */
/*   Updated: 2022/08/16 14:51:45 by christopher      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	speak(t_philo philo, char *msg)
{
	suseconds_t elapsed;

	elapsed = get_time();
	pthread_mutex_lock(&philo.params->m_speak);
	printf("%ld %d %s\n", get_elapsed_time(philo.params->init_time, elapsed), philo.id, msg);
	pthread_mutex_unlock(&philo.params->m_speak);
	
}

void	block_first_turn(t_philo philo)
{
	if (philo.id % 2)
		speak(philo, TAKE);
}

void	*routine(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	block_first_turn(philo);
	usleep(10000);
	(void)philo;
	return (NULL);
}
