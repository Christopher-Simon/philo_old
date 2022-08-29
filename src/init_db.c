/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_db.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christopher <christopher@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:28:40 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/27 13:28:13 by christopher      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	print_params(t_params *params, t_philo philo)
{
	printf("\nPRINT PARAMS\n");
	printf("fork : %d\n", params->fork);
	printf("fork : %p\n", &params->fork);
	printf("time to die : %d\n", philo.time_to_die);
	printf("time to eat : %d\n", philo.time_to_eat);
	printf("time to sleep : %d\n", philo.time_to_sleep);
	if (philo.round)
		printf("nb round  : %d\n", philo.round);
}

void	print_philo(t_philo philo)
{
	printf("je suis le philo %d\n", philo.id);
		printf("Mon adresse est %p\n", &philo);
		printf("ma fork est la : %d et la suivante : %d\n", philo.fork, philo.next_fork);
}


void	print_all_philo(t_philo *philo)
{
	int	nb_philo;
	int	i;

	i = 0;
	nb_philo = philo[i].params->fork;
	printf("\nPRINT PHILO\n");
	while (i < nb_philo)
	{
		print_philo(philo[i]);
		i++;
	}
}
