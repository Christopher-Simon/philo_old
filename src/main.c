/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chsimon <chsimon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:41:05 by chsimon           #+#    #+#             */
/*   Updated: 2022/08/23 18:08:53 by chsimon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// void	*routine(void *arg)
// {
// 	t_data *data;

// 	usleep(100);
	
// 	data = *(t_data **)arg;
// 	// int				test;
// 	// int				i;
// 	// int				j;
// 	// pthread_mutex_t	eat;

// 	// i = *(int *)arg;
// 	// if (i + 1 >= nb)
// 	// 	j = 0;
// 	// else
// 	// 	j = i + 1;
// 	// test = 0;
// 	// while (test < 4)	
// 	// {
// 	// 	pthread_mutex_init(&eat, NULL);
// 	// 	fork[i];
// 	// 	printf("data[%d] grabs fork[%d] and fork[%d]\n", i, i, i + 1);
// 	// 	pthread_mutex_destroy(&eat);
// 	// 	test++;
// 	// }
// 	ft_printf("je suis le philo : %d\n", data->nb);
// 	return (NULL);
// }

// int	end_philo(int nb, pthread_t	*th_philo, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < nb)
// 	{
// 		if (sc_pthread_join(th_philo[i], NULL))
// 			return (1);
// 		i++;
// 	}
// 	sc_pthread_mutex_destroy(&data->mutex);
// 	free(th_philo);
// 	free(data);
// 	return (0);
// }


int	philo(char **argv)
{
	t_philo	*philo;
	int		ret;

	philo =	init_struct_philo(argv);
	if (!philo)
		return (1);
	if (init_mutex(philo[0].params))
	{
		free(philo);
		return (1);
	}
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
