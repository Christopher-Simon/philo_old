/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:42:37 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/25 20:33:00 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	saint_chro_start(t_philo philo)
{
	while (philo.init_time >= get_time())
		usleep(150);
	return (0);
}

int	is_dead(t_philo philo)
{
	int	ret;
	time_t	elapsed;

	ret = 0;
	if (philo.cycle_time + philo.time_to_die < get_time())
	{
		pthread_mutex_lock(&philo.params->m_death);
		if (philo.params->death == 0)
		{
			philo.params->death = 1;
			elapsed = get_time();
			printf("%ld %d %s\n", elapsed - philo.init_time, philo.id, DIE);
		}
		pthread_mutex_unlock(&philo.params->m_death);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&philo.params->m_death);
		ret = philo.params->death;
		pthread_mutex_unlock(&philo.params->m_death);
	}
	return (ret);
}

int	is_gonna_die(time_t wait_time, time_t death_time)
{
	if (wait_time > death_time)
		return (1);
	return (0);
}


elapsed
init_time
cycle

death if

cycle + attente + eat + sleep



cycle + attente + die

pour le eat :
cycle + eat < cycle + die

pour le sleep : 
cycle + attente + sleep < cycle + die

check la mort avant de chopper les fourchettes



int	wait(time_t wait_time)
{
	while (!ret && wait_time >= get_time())
		usleep(50);
}