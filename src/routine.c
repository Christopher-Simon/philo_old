/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:33:46 by christopher       #+#    #+#             */
/*   Updated: 2022/08/26 19:25:31 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	speak(t_philo philo, char *msg)
{
	time_t	elapsed;
	int		ret;

	pthread_mutex_lock(&philo.params->m_death);
	ret = philo.params->death;
	if (!ret)
	{
		elapsed = get_time();
		printf("%ld %d %s\n", elapsed - philo.init_time, philo.id, msg);
	}
	pthread_mutex_unlock(&philo.params->m_death);
	return (ret);
}

int	philo_inception(t_philo philo)
{
	int	ret;
	time_t	now;
	time_t	wait;

	ret = speak(philo, SLEEP);
	now = get_time();
	wait = now + philo.time_to_sleep;
	while (!ret && wait >= get_time())
		usleep(90);
	if (!ret)
		ret = speak(philo, THINK);
	// if (philo.impair)
	// {
	// 	wait = wait + philo.time_to_eat / 2;
	// 	while (!ret && wait >= get_time())
	// 		usleep(90);
	// }
	return (ret);
}

int	action_fork(t_philo philo, int fork)
{
	int		ret;

	ret = 0;
	pthread_mutex_lock(&philo.params->m_fork[fork]);
	ret = speak(philo, TAKE);
	if (ret)
		pthread_mutex_unlock(&philo.params->m_fork[fork]);
	return (ret);
}

int	take_fork(t_philo philo, int fork_1, int fork_2)
{
	if (action_fork(philo, fork_1))
		return (1);
	if (action_fork(philo, fork_2))
	{
		pthread_mutex_unlock(&philo.params->m_fork[fork_1]);
		return (1);
	}
	return (0);
}

void	release_fork(t_philo philo, int fork_1, int fork_2)
{
	pthread_mutex_unlock(&philo.params->m_fork[fork_1]);
	pthread_mutex_unlock(&philo.params->m_fork[fork_2]);
}

int	philo_eat(t_philo *philo)
{
	int		ret;
	time_t	wait;

	ret = 0;
	if ((*philo).id % 2 != 1)
		ret = take_fork((*philo), (*philo).fork, (*philo).next_fork);
	else
		ret = take_fork((*philo), (*philo).next_fork, (*philo).fork);
	if (ret)
		return (1);
	ret = speak((*philo), EAT);
	update_cycle(philo);
	wait = (*philo).cycle_time + (*philo).time_to_eat;
	while (!ret && wait >= get_time())
		usleep(90);
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
