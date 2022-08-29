/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:40:17 by christopher       #+#    #+#             */
/*   Updated: 2022/08/27 19:13:28 by christopher      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	end_mutex(pthread_mutex_t *mutex, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		sc_pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(mutex);
	return (0);
}

int	destroy_params(t_params *params)
{
	if (params->m_cycle)
		end_mutex(params->m_cycle, params->fork);
	if (params->m_fork)
		end_mutex(params->m_fork, params->fork);
	if (&params->m_speak)
		sc_pthread_mutex_destroy(&params->m_speak);
	if (&params->m_stop)
		sc_pthread_mutex_destroy(&params->m_stop);
	if (&params->m_death)
		sc_pthread_mutex_destroy(&params->m_death);
	if (params->used)
		free(params->used);
	free(params);
	return (1);
}

int	destroy_philo(t_philo *philo)
{
	destroy_params(philo->params);
	free(philo);
	return (0);
}