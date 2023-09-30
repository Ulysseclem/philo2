/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:05:03 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/30 17:52:56 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philo(t_philo *philo, char **av, t_data *data)
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
		philo[i].data = data;
		i++;
	}
}

void	init_data(t_data *data)
{
	data->dead_flag = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->count)
	{
		pthread_mutex_init(&forks[i], NULL);
		philo[i].l_fork = &forks[i];
		if (philo[i].id == 1)
			philo[i].r_fork = &forks[philo->count - 1];
		if (philo[i].id > 1)
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_all(t_data *d, t_philo *p, pthread_mutex_t *f, char **av)
{
	init_philo(p, av, d);
	init_forks(f, p);
	init_data(d);
}