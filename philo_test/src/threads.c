/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:56:20 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/30 17:55:25 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag != 0)
		return (pthread_mutex_unlock(&philo->data->dead_lock), 1);
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

int	eat_count(t_philo *philo)
{
	if (philo->must_eat == -1)
		return (0);
	else if (philo->must_eat > philo->count_meal)
		return (0);
	return (1);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while(eat_count(philo) == 0 && is_philo_dead(philo) == 0)
	{
		eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	threads_maker(t_philo *philo)
{
	int	i;
	
	i = -1;
	while (++i < philo->count)
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
	i = -1;
	while (++i < philo->count)
		pthread_join(philo[i].thread, NULL);
}