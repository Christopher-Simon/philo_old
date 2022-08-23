/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:33:46 by christopher       #+#    #+#             */
/*   Updated: 2022/08/23 18:41:05 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	speak(t_philo philo, char *msg)
{
	time_t	elapsed;

	elapsed = get_time();
	pthread_mutex_lock(&philo.params->m_speak);
	printf("%ld %d %s\n", elapsed - philo.init_time, philo.id, msg);
	pthread_mutex_unlock(&philo.params->m_speak);
}

void	catch_fork_righty(t_philo philo)
{
	pthread_mutex_lock(&philo.params->m_fork[philo.next_id]);
	speak(philo, TAKE);
	pthread_mutex_lock(&philo.params->m_fork[philo.id]);
	speak(philo, TAKE);
	speak(philo, EAT);
	usleep(10000);
	pthread_mutex_unlock(&philo.params->m_fork[philo.next_id]);
	pthread_mutex_unlock(&philo.params->m_fork[philo.id]);
}

void	catch_fork_lefty(t_philo philo)
{
	pthread_mutex_lock(&philo.params->m_fork[philo.id]);
	speak(philo, TAKE);
	pthread_mutex_lock(&philo.params->m_fork[philo.next_id]);
	speak(philo, TAKE);
	speak(philo, EAT);
	usleep(10000);
	pthread_mutex_unlock(&philo.params->m_fork[philo.id]);
	pthread_mutex_unlock(&philo.params->m_fork[philo.next_id]);
	speak(philo, SLEEP);
}

// int	check_death()
// {
// 	suseconds_t death_time;

// 	while (1)
	// if (init time + death time < get_time || init time + eat_time < get_time)
	// 	break;
// 		return (1);

// 	return (0);
// }

void	routine_test(t_philo philo)
{
	int	i;

	i = 0;
	while (philo.round != 0)
	{
		// if (philo.id % 2)
		// 	catch_fork_righty(philo);
		// else
		// 	catch_fork_lefty(philo);
		// check_death(philo);
		while (1)
		{
			usleep(10);
			i++;
			if (philo.init_time + philo.time_to_die < get_time())
				break ;
		}
		speak(philo, DIE);
		printf("i : %d\n", i);
		if (philo.round != -1)
			philo.round--;
	}
}

void	*routine(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	philo.init_time = get_time();
	routine_test(philo);
	return (NULL);
}
