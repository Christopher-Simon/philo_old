/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:42:22 by christopher       #+#    #+#             */
/*   Updated: 2022/08/22 18:55:02 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

t_params	*get_params(char **argv)
{
	t_params		*params;

	params = ft_calloc(sizeof(t_params), 1);
	if (!params)
		return (NULL);
	params->fork = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		params->round = ft_atoi(argv[5]);
	else
		params->round = 0;
	return (params);
}

void	print_params(t_params params)
{
	printf("PRINT PARAMS\n");
	printf("fork : %d\n", params.fork);
	printf("time to die : %d\n", params.time_to_die);
	printf("time to eat : %d\n", params.time_to_eat);
	printf("time to sleep : %d\n", params.time_to_sleep);
	if (params.round)
		printf("nb round  : %d\n", params.round);
}

void	print_philo(t_philo *philo)
{
	int	nb_philo;
	int	i;

	i = 0;
	nb_philo = philo[i].params->fork;
	while (i < nb_philo)
	{
		printf("je suis le philo %d\n", philo[i].id);
		printf("je suis le philo %p\n", &philo[i].id);
		i++;
	}
}

int	set_philo(t_philo *philo, int nb_philo, char **argv)
{
	int			i;
	t_params	*params;

	params = get_params(argv);
	if (!params)
		return (1);
	i = 1;
	while (i <= nb_philo)
	{
		philo[i - 1].id = i;
		if (i == nb_philo)
			philo[i - 1].next_id = 1;
		else
			philo[i - 1].next_id = i + 1;
		philo[i - 1].params = params;
		i++;
	}
	return (0);
}

t_philo	*init_struct_philo(char **argv)
{
	t_philo	*philo;
	int		nb_philo;

	nb_philo = ft_atoi(argv[1]);
	philo = ft_calloc(sizeof(t_philo), nb_philo);
	if (!philo)
		return (NULL);
	if (set_philo(philo, nb_philo, argv))
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}

