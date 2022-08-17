/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:24:24 by christopher       #+#    #+#             */
/*   Updated: 2022/08/16 14:45:03 by christopher      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

suseconds_t	get_time(void)
{
	struct timeval	get_time;

	if (sc_gettimeofday(&get_time, NULL))
		return (-1);
	return (get_time.tv_usec);
}

suseconds_t	get_elapsed_time(suseconds_t time1, suseconds_t time2)
{
	suseconds_t		ret;

	ret = (time2 / 1000) - (time1 / 1000);
	return (ret);	
}
