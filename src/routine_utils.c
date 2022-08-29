/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:42:37 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/29 14:34:52 by christopher      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// int	saint_chro_start(t_philo philo)
// {
// 	while (philo.init_time - 1 >= get_time())
// 		usleep(90);
// 	return (0);
// }


int	saint_chro_start(t_philo philo)
{
	time_t	time;

	time = 1;
	while (time > 0)
	{
		time = philo.init_time - get_time();
		if (time > 1000)
			usleep(500);
		else if (time > 0)
			usleep(time / 10);
	}
	return (0);
}

int	net_usleep(time_t time_to_wait)
{
	time_t	time;

	time = 1;
	while (time > 0)
	{
		time = time_to_wait - get_time();
		if (time > 1000)
			usleep(500);
		else if (time > 0)
			usleep(time / 10);
	}
	return (0);
}


int	is_dead(t_philo philo)
{
	// int	ret;
	time_t	elapsed;

	// ret = 0;
	// if (philo.cycle_time + philo.time_to_die < get_time())
	// {
		pthread_mutex_lock(&philo.params->m_death);
		if (philo.params->death == 0)
		{
			philo.params->death = 1;
			elapsed = get_time();
			printf("%ld %d %s\n", elapsed - philo.init_time, philo.id, DIE);
		}
		pthread_mutex_unlock(&philo.params->m_death);
		return (1);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo.params->m_death);
	// 	ret = philo.params->death;
	// 	pthread_mutex_unlock(&philo.params->m_death);
	// }
	// return (ret);
}

time_t	time_to_wait(time_t wait_time, time_t death_time)
{
	if (wait_time > death_time)
		return (death_time);
	return (wait_time);
}

int	update_cycle(t_philo *philo, t_params *params)
{
	pthread_mutex_lock(&params->m_cycle[philo->fork]);
	philo->cycle_time = get_time();
	if (DB_HADES)
	{
		print_philo((*philo));
		printf("mutex %d, ID : %d new cycle time is %ld, with %p\n\n", philo->fork, philo->id, philo->cycle_time, &philo->cycle_time);

	}
	pthread_mutex_unlock(&params->m_cycle[philo->fork]);
	return (0);
}

// pour le eat :
// cycle + eat < cycle + die

// pour le sleep : 
// cycle + attente + sleep < cycle + die
// now + sleep < cycle + die


// check la mort avant de chopper les fourchettes
