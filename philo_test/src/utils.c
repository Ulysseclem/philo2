/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:37:24 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/30 18:25:46 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds && is_philo_dead(philo) == 0)
		usleep(500);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long long int	num;
	int				i;
	long long int	neg;

	i = 0;
	num = 0;
	neg = 1;
	while ((nptr[i] >= 8 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * neg);
}
void	print_txt(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", get_current_time() - philo->start, philo->id, str);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
}

void	print_died(t_philo *philo)
{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->dead_flag++;
		if (philo->data->dead_flag == 1)
			printf("%ld %d died\n", get_current_time() - philo->start, philo->id);
		pthread_mutex_unlock(&philo->data->dead_lock);
}
