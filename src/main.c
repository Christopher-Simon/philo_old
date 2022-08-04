/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:41:05 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/04 14:54:35 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = *(t_philo **)arg;
	// int				test;
	// int				i;
	// int				j;
	// pthread_mutex_t	eat;

	// i = *(int *)arg;
	// if (i + 1 >= nb)
	// 	j = 0;
	// else
	// 	j = i + 1;
	// test = 0;
	// while (test < 4)	
	// {
	// 	pthread_mutex_init(&eat, NULL);
	// 	fork[i];
	// 	printf("philo[%d] grabs fork[%d] and fork[%d]\n", i, i, i + 1);
	// 	pthread_mutex_destroy(&eat);
	// 	test++;
	// }
	ft_printf("je suis le philo : %d", philo->nb);
	return (NULL);
}

t_philo	*get_data(char **argv)
{
	t_philo	*philo;

	philo = ft_calloc(sizeof(t_philo), 1);
	if (!philo)
		return (NULL);
	philo->fork = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->round = ft_atoi(argv[5]);
	return (philo);
}

int	init_philo(t_philo *philo)
{
	pthread_t	**th_philo;

	th_philo = malloc(sizeof(pthread_t *) * philo->fork);
	if (!th_philo)
		return (1);
	philo->nb = 0;
	ft_printf("test");
	while (philo->nb < philo->fork)
	{
		ft_printf("%d\n", philo->nb);
		if (sc_pthread_create(th_philo[philo->nb], NULL, &routine, &philo))
				return (1);
		philo->nb++;
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

int	init_time()
{
	struct timeval	time_init;
	struct timeval	time_2;

	if (sc_gettimeofday(&time_init, NULL))
		return (1);
	printf("time : %ld\n", time_init.tv_usec);
	usleep(45000);
	if (sc_gettimeofday(&time_2, NULL))
		return (1);
	printf("time : %ld\n", (time_2.tv_usec / 1000) - (time_init.tv_usec / 1000));
	return (0);
}


int	philo(char **argv)
{
	t_philo		*philo;

	philo = get_data(argv);
	if (!philo)
		return (1);
	init_philo(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (1);
	if (argv[5] && ft_atoi(argv[5]) == 0)
		return (0);
	philo(argv);
	printf("zizi\n");
	return (0);
}
