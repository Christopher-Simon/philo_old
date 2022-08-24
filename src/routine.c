/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:33:46 by christopher       #+#    #+#             */
/*   Updated: 2022/08/24 18:37:53 by chsimon          ###   ########.fr       */
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

void	take_fork(t_philo philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&philo.params->m_fork[fork_1]);
	speak(philo, TAKE);
	pthread_mutex_lock(&philo.params->m_fork[fork_2]);
	speak(philo, TAKE);
}

void	release_fork(t_philo philo, int fork_1, int fork_2)
{
	pthread_mutex_unlock(&philo.params->m_fork[fork_1]);
	pthread_mutex_unlock(&philo.params->m_fork[fork_2]);
}

int	philo_inception(t_philo philo)
{
	int	ret;

	ret = 0;
	speak(philo, SLEEP);
	while (philo.cycle_time + philo.time_to_eat + philo.time_to_sleep >= get_time())
	{
		usleep(50);
		if (is_dead(philo))
		{
			speak(philo, DIE);
			ret++;
			break;
		}
	}
	return (ret);
}

int	philo_eat(t_philo *philo)
{
	int	ret;

	ret = 0;
	if ((*philo).id % 2 != 1)
		take_fork((*philo), (*philo).fork, (*philo).next_fork);
	else
		take_fork((*philo), (*philo).next_fork, (*philo).fork);
	if ((*philo).cycle_time != 0 && is_dead(*philo))
		ret++;
	else
		speak((*philo), EAT);
	(*philo).cycle_time = get_time();
	while (!ret && (*philo).cycle_time + (*philo).time_to_eat >= get_time())
	{
		usleep(50);
		if (is_dead(*philo))
			ret++;
	}
	if ((*philo).id % 2 != 1)
		release_fork((*philo), (*philo).fork, (*philo).next_fork);
	else 
		release_fork((*philo), (*philo).next_fork, (*philo).fork);
	if (ret)
		speak(*philo, DIE);
	return (ret);
}

void	routine_test(t_philo philo)
{
	if (philo.id % 2 != 1)
		usleep(10000);
	while (philo.round != 0)
	{
		if (philo_eat(&philo))
			break;
		if (philo_inception(philo))
			break;
		if (philo.round != -1)
			philo.round--;
	}
	speak(philo, "end");
}

void	*routine(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	// if (DB_PRMS_TH && philo.id == 1)

	printf("sleep_time : %d\n", philo.time_to_sleep);
	saint_chro_start(philo);
	routine_test(philo);
	return (NULL);
}
