/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:41:05 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/01 16:55:26 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*routine(void *arg)
{
	int				test;
	int				i;
	int				j;
	pthread_mutex_t	eat;

	i = *(int *)arg;
	if (i + 1 >= nb)
		j = 0;
	else
		j = i + 1;
	test = 0;
	while (test < 4)	
	{
		pthread_mutex_init(&eat, NULL);
		philo[i];
		fork[i];
		printf("philo[%d] grabs fork[%d] and fork[%d]\n", i, i, i + 1);
		pthread_mutex_destroy(&eat);
		test++;
	}
	return (NULL);
}


int	init_philo(int	nb, pthread_t	**philo)
{
	int			*fork;
	int			i;

	*philo = malloc(sizeof(pthread_t) * nb);
	if (!*philo)
		return (1);
	fork = malloc(sizeof(int) * nb);
	if (!fork)
		return (1);
	i = 0;
	while (i < nb)
	{
		if (sc_pthread_create(philo[i], NULL, &routine, &i))
				return (1);
		i++;
	}
	return (0);
}

int	end_philo(int nb, pthread_t	**philo)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (sc_pthread_join(*philo[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	eat(void)
{
	
}

int	init_time()
{
	struct timeval time_init;
	struct timeval time_2;
	if (sc_gettimeofday(&time_init, NULL))
		return (1);
	printf("time : %ld\n", time_init.tv_usec);
	usleep(45000);
	if (sc_gettimeofday(&time_2, NULL))
		return (1);
	printf("time : %ld\n", (time_2.tv_usec / 1000) - (time_init.tv_usec / 1000));
	return (0);
}


int	philo(int nb)
{
	pthread_t	*philo;


	init_philo(nb, &philo)
	


	return (0);
}

int	main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	philo(2);
	printf("zizi\n");
	return (0);
}
