/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:42:22 by christopher       #+#    #+#             */
/*   Updated: 2022/08/23 18:29:34 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

t_params	*get_params(char **argv)
{
	t_params	*params;

	params = ft_calloc(sizeof(t_params), 1);
	if (!params)
		return (NULL);
	params->fork = ft_atoi(argv[1]);
	return (params);
}

void	print_params(t_params *params, t_philo philo)
{
	printf("PRINT PARAMS\n");
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
	while (i < nb_philo)
	{
		printf("je suis le philo %d\n", philo[i].id);
		printf("je suis le philo %p\n", &philo[i].id);
		i++;
	}
}

void	data_philo(t_philo *philo, int nb_philo, char **argv)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philo[i].round = ft_atoi(argv[5]);
		else
			philo[i].round = -1;	
		i++;
	}
}

void	id_philo(t_philo *philo, int nb_philo, t_params *params)
{
	int	i;

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
}

int	set_philo(t_philo *philo, int nb_philo, char **argv)
{
	t_params	*params;

	params = get_params(argv);
	if (!params)
		return (1);
	data_philo(philo, nb_philo, argv);
	id_philo(philo, nb_philo, params);
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
	// print_params(philo[0].params, philo[0]);
	return (philo);
}

