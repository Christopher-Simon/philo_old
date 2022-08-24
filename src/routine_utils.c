/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:42:37 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/24 16:23:29 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	saint_chro_start(t_philo philo)
{
	while (philo.init_time >= get_time())
		usleep(50);
	return (0);
}

int	is_dead(t_philo philo)
{
	if (philo.cycle_time + philo.time_to_die < get_time())
		return (1);
	return (0);
}
