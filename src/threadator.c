/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:26:40 by christopher       #+#    #+#             */
/*   Updated: 2022/08/26 19:30:54 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	end_philo_thread(int nb, pthread_t	*th_philo)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (sc_pthread_join(th_philo[i], NULL))
			return (1);
		i++;
	}
	free(th_philo);
	return (0);
}

int	set_time_philo(t_philo *philo, int nb_philo, t_params *params)
{
	int		i;
	time_t	start_time;

	i = 0;
	start_time = get_time();
	if (start_time == -1)
		return (1);
	params->init_time = start_time + 1000;
	while (i < nb_philo)
	{
		philo[i].init_time = params->init_time;
		philo[i].cycle_time = philo[i].init_time;
		i++;
	}
	return (0);
}

int	create_thread(t_philo *philo, pthread_t *th_philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (sc_pthread_create(&th_philo[i], NULL, &routine, &philo[i]))
		{
			while (i-- >= 0)
				sc_pthread_join(th_philo[i], NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

int	shinigami(t_philo *philo, t_params *params, int nb_philo)
{
	int		i;
	time_t	death;
	time_t	init;
	int		ret;

	i = 0;
	death = params->time_to_die;
	init = params->init_time;
	ret = 1;
	while (ret)
	{
		i = 0;
		while (i < nb_philo)
		{	
			pthread_mutex_lock(&params->m_cycle[i]);
			printf("%d\n", i);
			philo[i].cycle_time = get_time();	
			if (philo[i].cycle_time + death < get_time())
			{
				pthread_mutex_lock(&params->m_death);
				params->death = 1;
				printf("%ld %d %s\n", get_time() - init, philo[i].id, DIE);
				pthread_mutex_unlock(&params->m_death);
				ret = 0;
			}
			pthread_mutex_unlock(&params->m_cycle[i]);
			if (!ret)
				break;
			usleep(500);
			i++;	
		}
	}
	return (0);
}

int	threadator(t_philo *philo, t_params *params)
{
	pthread_t	*th_philo;
	int			nb_philo;

	(void)params;
	nb_philo = philo[0].params->fork;
	th_philo = malloc(sizeof(pthread_t) * nb_philo);
	if (!th_philo)
		return (1);
	set_time_philo(philo, nb_philo, params); //TODO secu
	if (create_thread(philo, th_philo, nb_philo))
		return (1);
	shinigami(philo, params, nb_philo);
	end_philo_thread(nb_philo, th_philo);
	return (0);
}
