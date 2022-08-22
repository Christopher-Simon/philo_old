/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:26:40 by christopher       #+#    #+#             */
/*   Updated: 2022/08/22 18:38:40 by chsimon          ###   ########.fr       */
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

int	set_time_philo(t_philo *philo, int nb_philo)
{
	int			i;
	suseconds_t	start_time;

	i = 0;
	start_time = get_time();
	if (start_time == -1)
		return (1);
	while (i < nb_philo)
	{
		philo[i].wait_time = start_time + 1000;
		i++;
	}
	return (0);
}


int	threadator(t_philo *philo, t_params *params)
{
	pthread_t	*th_philo;
	int			nb_philo;
	int			i;

	i = 0;
	nb_philo = philo[0].params->fork;
	th_philo = malloc(sizeof(pthread_t) * nb_philo);
	if (!th_philo)
		return (1);
	pthread_mutex_lock(&params->m_go);
	philo[0].params->init_time = get_time();
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
	// if (set_time_philo(philo, nb_philo))
	// 	return (1); //TODO SECU
	pthread_mutex_unlock(&params->m_go);
	end_philo_thread(nb_philo, th_philo);
	return (0);
}
