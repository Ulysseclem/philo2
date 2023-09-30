/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:05:03 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/30 17:21:58 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philo(t_philo *philo, pthread_mutex_t *forks, char **av, t_data *data)
{
	int i;
	int	nb_philo;

	nb_philo = ft_atoi(av[1]);

	i = 0;
	while (i < nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].count = nb_philo;
		philo[i].ttdie = (u_int64_t)ft_atoi(av[2]);
		philo[i].tteat = (u_int64_t)ft_atoi(av[3]);
		philo[i].ttsleep = (u_int64_t)ft_atoi(av[4]);
		if (!av[5])
			philo[i].must_eat = -1;
		else
			philo[i].must_eat = (u_int64_t)ft_atoi(av[5]);
		philo[i].start = get_current_time();
		philo[i].lastmeal = get_current_time();
		philo[i].count_meal = 0;
		philo[i].dead = 0;
		philo[i].l_fork = &forks[i];
		philo[i].data = data;
		if (philo[i].id == 1)
			philo[i].r_fork = &forks[nb_philo - 1];
		if (philo[i].id > 1)
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_data(t_data *data, int count)
{
	data->count = count;
	data->dead_flag = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_all(t_data *data, t_philo *philo, pthread_mutex_t *forks, char **av)
{
	int count;
	
	count = ft_atoi(av[1]);
	init_forks(forks, count);
	init_philo(philo, forks, av, data);
	init_data(data, count);
}