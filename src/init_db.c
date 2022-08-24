/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_db.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:28:40 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/24 17:02:39 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	print_params(t_params *params, t_philo philo)
{
	printf("\nPRINT PARAMS\n");
	printf("fork : %d\n", params->fork);
	printf("time to die : %d\n", philo.time_to_die);
	printf("time to eat : %d\n", philo.time_to_eat);
	printf("time to sleep : %d\n", philo.time_to_sleep);
	if (philo.round)
		printf("nb round  : %d\n", philo.round);
}

void	print_philo(t_philo *philo)
{
	int	nb_philo;
	int	i;

	i = 0;
	nb_philo = philo[i].params->fork;
	printf("\nPRINT PHILO\n");
	while (i < nb_philo)
	{
		printf("je suis le philo %d\n", philo[i].id);
		printf("Mon adresse est %p\n", &philo[i].id);
		printf("ma fork est la : %d et la suivante : %d\n", philo[i].fork, philo[i].next_fork);
		i++;
	}
}
