/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:33:46 by christopher       #+#    #+#             */
/*   Updated: 2022/08/25 19:01:07 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	speak(t_philo philo, char *msg)
{
	time_t	elapsed;
	int		ret;

	// pthread_mutex_lock(&philo.params->m_speak);
	pthread_mutex_lock(&philo.params->m_death);
	ret = philo.params->death;
	if (!ret)
	{
		elapsed = get_time();
		printf("%ld %d %s\n", elapsed - philo.init_time, philo.id, msg);
	}
	pthread_mutex_unlock(&philo.params->m_death);
	// pthread_mutex_unlock(&philo.params->m_speak);
	return (ret);
}

int	philo_inception(t_philo philo)
{
	int	ret;

	ret = speak(philo, SLEEP);
	while (!ret && philo.cycle_time + philo.time_to_eat + philo.time_to_sleep >= get_time())
	{
		usleep(500);
		ret = is_dead(philo);
	}
	if (!ret)
		speak(philo, THINK);
	// if (philo.impair)
	// 	usleep(50000);
	return (ret);
}

int	action_fork(t_philo philo, int fork)
{
	int	ret;
	int	taken;

	ret = 0;
	taken = 1;
	while (taken)
	{
		if (is_dead(philo))
			return (1);
		pthread_mutex_lock(&philo.params->m_fork[fork]);
		if (philo.params->used[fork] == DISPO)
		{
			philo.params->used[fork] = UNDISPO;
			taken = 0;
			ret = speak(philo, TAKE);
		}
		pthread_mutex_unlock(&philo.params->m_fork[fork]);
	}
	return (ret);
}

int	take_fork(t_philo philo, int fork_1, int fork_2)
{
	if (action_fork(philo, fork_1))
		return (1);
	if (action_fork(philo, fork_2))
		return (1);
	return (0);
}

void	release_fork(t_philo philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&philo.params->m_fork[fork_1]);
	philo.params->used[fork_1] = DISPO;
	pthread_mutex_unlock(&philo.params->m_fork[fork_1]);
	pthread_mutex_lock(&philo.params->m_fork[fork_2]);
	philo.params->used[fork_2] = DISPO;
	pthread_mutex_unlock(&philo.params->m_fork[fork_2]);
}

int	philo_eat(t_philo *philo)
{
	int	ret;

	ret = 0;
	if ((*philo).id % 2 != 1)
		ret = take_fork((*philo), (*philo).fork, (*philo).next_fork);
	else
		ret = take_fork((*philo), (*philo).next_fork, (*philo).fork);
	if (!ret)
		speak((*philo), EAT);
	(*philo).cycle_time = get_time();
	while (!ret && (*philo).cycle_time + (*philo).time_to_eat >= get_time())
	{
		usleep(500);
		ret = is_dead(*philo);
	}
	if ((*philo).id % 2 != 1)
		release_fork((*philo), (*philo).fork, (*philo).next_fork);
	else 
		release_fork((*philo), (*philo).next_fork, (*philo).fork);
	return (ret);
}

void	routine_test(t_philo philo)
{
	if (philo.id % 2 != 1)
		usleep(10000);
	philo.cycle_time = philo.init_time;
	while (philo.round != 0)
	{
		if (philo_eat(&philo))
			break;
		if (philo_inception(philo))
			break;
		if (philo.round != -1)
			philo.round--;
	}
}

void	*routine(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	if (DB_PRMS_TH && philo.id == 1)
	{
		printf("sleep_eat : %d\n", philo.time_to_eat);
		printf("sleep_eat : %p\n", &philo.time_to_eat);
		printf("impair : %d\n", philo.impair);
		printf("impair : %p\n", &philo.time_to_eat);
	}
	saint_chro_start(philo);
	routine_test(philo);
	return (NULL);
}
