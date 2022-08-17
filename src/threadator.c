/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:26:40 by christopher       #+#    #+#             */
/*   Updated: 2022/08/16 13:35:50 by christopher      ###   ########.fr       */
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

int	threadator(t_philo *philo)
{
	pthread_t	*th_philo;
	int			nb_philo;
	int			i;

	i = 0;
	nb_philo = philo[0].params->fork;
	th_philo = malloc(sizeof(pthread_t) * nb_philo);
	if (!th_philo)
		return (1);
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
	end_philo_thread(nb_philo, th_philo); 
	return (0);
}
