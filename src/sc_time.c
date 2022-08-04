/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:52:50 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/01 10:55:11 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	sc_gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz)
{
	if (gettimeofday(tv, tz))
	{
		perror("get_time_of_day"); //TODO TO REMOVE
		return (1);
	}
	return (0);
}