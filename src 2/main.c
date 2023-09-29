/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:28:02 by uclement          #+#    #+#             */
/*   Updated: 2023/09/29 14:37:41 by uclement         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data			*data;

	if (parse_args(ac, av) != 0)
	{
		printf("Wrong input\n");
		return (0);
	}
	data = malloc(sizeof(t_data));
	init_all(data, av);
	threads_maker(data);
	threads_breaker(data);
	free(data->fork);
	free(data->philo);
	free(data);
	return (0);
}
