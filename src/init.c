/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:42:22 by christopher       #+#    #+#             */
/*   Updated: 2022/08/26 12:44:47 by chsimon          ###   ########.fr       */
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

void	data_philo(t_philo **philo, int nb_philo, char **argv)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		(*philo)[i].time_to_die = ft_atoi(argv[2]);
		(*philo)[i].time_to_eat = ft_atoi(argv[3]);
		(*philo)[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			(*philo)[i].round = ft_atoi(argv[5]);
		else
			(*philo)[i].round = -1;
		if (nb_philo % 2)
			(*philo)[i].impair = 1;
		else
			(*philo)[i].impair = 0;
		i++;
	}
}

void	id_philo(t_philo **philo, int nb_philo, t_params *params)
{
	int	i;

	i = 1;
	while (i <= nb_philo)
	{
		(*philo)[i - 1].id = i;
		(*philo)[i - 1].fork = i - 1;
		if (i != nb_philo)
			(*philo)[i - 1].next_fork = i;
		else
			(*philo)[i - 1].next_fork = 0;
		(*philo)[i - 1].params = params;
		// printf("%d\n", (*philo)[i - 1].id);
		// printf("%p\n", &(*philo)[i - 1].id);
		i++;
	}
}

int	set_philo(t_philo **philo, int nb_philo, char **argv)
{
	t_params	*params;

	params = get_params(argv);
	if (!params)
		return (1);
	data_philo(philo, nb_philo, argv);
	id_philo(philo, nb_philo, params);
	return (0);
}

int	init_struct_philo(char **argv,t_philo **philo)
{
	int		nb_philo;

	nb_philo = ft_atoi(argv[1]);
	*philo = ft_calloc(sizeof(t_philo), nb_philo);
	if (!*philo)
		return (1);
	if (set_philo(philo, nb_philo, argv))
	{
		free(philo);
		return (1);
	}
	return (0);
}

