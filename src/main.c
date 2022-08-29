/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:41:05 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/29 15:31:18 by christopher      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	philo(char **argv)
{
	t_philo	*philo;
	int		ret;

	if (init_struct_philo(argv, &philo))
		return (1);
	if (init_mutex(philo[0].params))
	{
		destroy_philo(philo);
		return (1);
	}
	if (DB_PARAMS)
		print_params(philo[0].params, philo[0]);
	if (DB_PHILO)
		print_all_philo(philo);
	
	ret = threadator(philo, philo[0].params);
	destroy_philo(philo);
	return (ret);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (1);
	if (argv[5] && ft_atoi(argv[5]) == 0)
		return (0);
	philo(argv);
	return (0);
}
