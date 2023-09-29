/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:56:20 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/29 23:09:19 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_txt(t_philo *philo, char *str)
{
	is_philo_dead(philo);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", get_current_time() - philo->start, philo->id, str);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->loop);
	while(philo->must_eat > philo->count_meal && philo->data->dead_flag == 0)
	{
		pthread_mutex_unlock(&philo->data->loop);
		eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		pthread_mutex_lock(&philo->data->loop);
	}
	pthread_mutex_unlock(&philo->data->loop);
	return (NULL);
}

void	threads_maker(t_philo *philo)
{
	int	i;
	
	i = 0;
	while (i < philo->count)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	i = -1;
	while (++i < philo->count)
		pthread_join(philo[i].thread, NULL);
}