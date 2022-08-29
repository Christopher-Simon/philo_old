/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shinigami.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:45:44 by christopher       #+#    #+#             */
/*   Updated: 2022/08/29 17:01:47 by christopher      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	check_death(t_philo *philo, t_params *params)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&params->m_cycle[philo->fork]);
	if (philo->cycle_time + params->time_to_die < get_time())
	{
		if (DB_HADES)
		{
			print_philo(*philo);
			printf("mutex %d, ID : %d cycle time was %ld, with %p\n", philo->fork, philo->id, philo->cycle_time, &philo->cycle_time);
		}
		pthread_mutex_lock(&params->m_death);
		ret = params->death;
		if (!ret)
		{
			params->death = 1;
			ret	= 1;
			printf("%ld %d %s\n", get_time() - philo->init_time, philo->id, DIE);
		}
		pthread_mutex_unlock(&params->m_death);
	}
	pthread_mutex_unlock(&params->m_cycle[philo->fork]);
	return (ret);
}

int	check_stop(t_params *params)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&params->m_stop);
	if (params->stop == params->fork)
	{
		pthread_mutex_lock(&params->m_death);
		params->death = 1;
		pthread_mutex_unlock(&params->m_death);
		ret = 1;
	}
	pthread_mutex_unlock(&params->m_stop);
	return (ret);
}

void	*shinigami(void *arg)
{
	t_philo		*philo;
	t_params	*params;
	int		ret;

	philo = (t_philo *)arg;
	params = philo->params;
	ret = 1;
	while (ret)
	{	
		if (check_death(philo, params) || check_stop(params))
			ret = 0;
		usleep(3000);
	}
	return (0);
}

int	create_shinigami(t_philo *philo, pthread_t *th_shinigami, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (sc_pthread_create(&th_shinigami[i], NULL, &shinigami, &philo[i]))
		{
			while (i-- >= 0)
				sc_pthread_join(th_shinigami[i], NULL);
			return (1);
		}
		i++;
	}
	return (0);
}
