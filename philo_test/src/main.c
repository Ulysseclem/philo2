/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:04:05 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/30 15:46:05 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parse_args(int ac, char **av)
{
	int i;
	int j;
	
	if (ac < 5  || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	threads_breaker(t_philo *philo, pthread_mutex_t *forks, t_data *data)
{
	int	i;

	i = -1;
	while (++i < philo->count)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->print);
}

int	main(int ac, char **av)
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				count;

	if (parse_args(ac, av) != 0)
	{
		printf("Wrong input\n");
		return (1);
	}
	count = ft_atoi(av[1]);
	data = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo) * count);
	forks = malloc(sizeof(pthread_mutex_t) * count);
	init_all(data, philo, forks, av);
	threads_maker(philo);
	threads_breaker(philo, forks, data);
	free(forks);
	free(philo);
	free(data);
	return (0);
}
