/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:34:54 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/30 16:34:05 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"



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
		if (philo->count == 1)
		{
			ft_usleep(philo->ttdie);
			philo->data->dead_flag++;
			if (philo->data->dead_flag == 1)
				printf("%ld %d died\n", get_current_time() - philo->start, philo->id);
			pthread_mutex_unlock(philo->r_fork);
			return ;
		}
		pthread_mutex_lock(philo->r_fork);
		print_txt(philo, "has taken a fork");
	}
	philo->lastmeal = get_current_time();		
	print_txt(philo, "is eating");
	philo->count_meal = philo->count_meal + 1;
	if ((philo->ttdie) <= philo->tteat)
	{
		ft_usleep(philo->ttdie);
		pthread_mutex_lock(&philo->data->dead_lock);
        philo->data->dead_flag++;
		if (philo->data->dead_flag == 1)
			printf("%ld %d died\n", get_current_time() - philo->start, philo->id);
		pthread_mutex_unlock(&philo->data->dead_lock);
	}
	else
		ft_usleep(philo->tteat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

}

void	philo_sleep(t_philo *philo)
{
	print_txt(philo, "is sleeping");
	if (is_philo_dead(philo) == 0)
	{
		if ((philo->tteat + philo->ttsleep) >= philo->ttdie)
		{
			ft_usleep(philo->ttdie - philo->tteat);
			pthread_mutex_lock(&philo->data->dead_lock);
			philo->data->dead_flag++;
			if (philo->data->dead_flag == 1)
				printf("%ld %d died\n", get_current_time() - philo->start, philo->id);
			pthread_mutex_unlock(&philo->data->dead_lock);
		}
		else
			ft_usleep(philo->ttsleep);
	}
}

void	philo_think(t_philo *philo)
{
	print_txt(philo, "is thinking");
	if (is_philo_dead(philo) == 0 && (philo->count % 2) == 1)
	{
		if ((philo->tteat * 3) >= philo->ttdie)
		{
			ft_usleep(philo->ttdie - (philo->tteat + philo->ttsleep) );
			pthread_mutex_lock(&philo->data->dead_lock);
			philo->data->dead_flag++;
			if (philo->data->dead_flag == 1)
				printf("%ld %d died\n", get_current_time() - philo->start, philo->id);
			pthread_mutex_unlock(&philo->data->dead_lock);
		}
	}
	if (is_philo_dead(philo) == 0 && (philo->count % 2) == 0)
	{
		if ((philo->tteat * 2) >= philo->ttdie)
		{
			ft_usleep(philo->ttdie - (philo->tteat + philo->ttsleep) );
			pthread_mutex_lock(&philo->data->dead_lock);
			philo->data->dead_flag++;
			if (philo->data->dead_flag == 1)
				printf("%ld %d died\n", get_current_time() - philo->start, philo->id);
			pthread_mutex_unlock(&philo->data->dead_lock);
		}
	}
	ft_usleep(1);
}