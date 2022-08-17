/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:40:17 by christopher       #+#    #+#             */
/*   Updated: 2022/08/16 12:55:17 by christopher      ###   ########.fr       */
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
	// int	i;

	// i = 0;
	// while (i < params->fork)
	// {
	// 	sc_pthread_mutex_destroy(&params->m_fork[i]);
	// 	i++;
	// }
	end_mutex(params->m_fork, params->fork);
	free(params);
	return (0);
}

int	destroy_philo(t_philo *philo)
{
	destroy_params(philo->params);
	free(philo);
	return (0);
}