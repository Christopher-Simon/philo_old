/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:51:16 by christopher       #+#    #+#             */
/*   Updated: 2022/08/22 18:26:26 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

pthread_mutex_t	*create_mutex(int nb)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = ft_calloc(sizeof(pthread_mutex_t), nb);
	if (!mutex)
		return (NULL);
	while (i < nb)
	{
		if (sc_pthread_mutex_init(&mutex[i], NULL))
		{
			while (i-- >= 0)
				sc_pthread_mutex_destroy(&mutex[i]);
			return (NULL);
		}
		i++;
	}
	return (mutex);
}

int	init_mutex(t_params *params)
{
	params->m_fork = create_mutex(params->fork);
	if (!params->m_fork)
		return (1);
	if (sc_pthread_mutex_init(&params->m_speak, NULL))
	{
		end_mutex(params->m_fork, params->fork);
		return (1);
	}
	if (sc_pthread_mutex_init(&params->m_go, NULL))
	{
		sc_pthread_mutex_destroy(&params->m_speak);
		end_mutex(params->m_fork, params->fork);
		return (1);
	}
	return (0);
}
