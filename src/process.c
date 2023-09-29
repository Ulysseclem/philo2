/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:34:54 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/29 22:31:41 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void is_philo_dead(t_philo *philo)
{
	if (((philo->lastmeal + philo->ttdie) < get_current_time())  && philo->is_eating != 1)
	{
        pthread_mutex_lock(&philo->data->dead_lock);
        philo->data->dead_flag = 1;
        pthread_mutex_unlock(&philo->data->dead_lock);
	}
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_txt(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_txt(philo, "has taken a fork");
	}
	else 
	{
		pthread_mutex_lock(philo->l_fork);
			print_txt(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
			print_txt(philo, "has taken a fork");
	}
	print_txt(philo, "is eating");
	philo->is_eating = 1;
	philo->lastmeal = get_current_time();
	philo->count_meal = philo->count_meal + 1;
	ft_usleep(philo->tteat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

}

void	philo_sleep(t_philo *philo)
{
	print_txt(philo, "is sleeping");
	ft_usleep(philo->ttsleep);
}

void	philo_think(t_philo *philo)
{
	print_txt(philo, "is thinking");
	ft_usleep(1);
}