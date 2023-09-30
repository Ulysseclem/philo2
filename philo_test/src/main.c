/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:04:05 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/09/30 18:21:04 by uclement         ###   ########.fr       */
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

void	free_all(t_philo *philo, pthread_mutex_t *forks, t_data *data)
{
	free(forks);
	free(philo);
	free(data);	
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
	if (!data)
		return (1);
	philo = malloc(sizeof(t_philo) * count);
	if (!philo)
		return (free(data), 1);
	forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		return(free(data), free(philo), 1);
	init_all(data, philo, forks, av);
	threads_maker(philo);
	threads_breaker(philo, forks, data);
	free_all(philo, forks, data);
	return (0);
}


/*

[+] Test #27 Succeeded with 200 410 200 200 

		[============[ Testing Invalid Arguments ]==============]

[~] Test #33 Program output multiple lines with 5 2147483649 200 200 5, you should decide if this case is handled well. Here are the last 2 lines:
 2602 3 is thinking
2801 1 is thinking 

[~] Test #34 Program output multiple lines with 5 200 2147483649 200 5, you should decide if this case is handled well. Here are the last 2 lines:
 0 4 is eating
200 1 died 

./test.sh: line 291: 241427 Segmentation fault      timeout 10 "$program_path/$program_name" "${params[@]}" &> output.txt
[~] Test #35 Program output with 2147483649 200 200 200 5:
 timeout: the monitored command dumped core 
[+] Test #36 Program ran successfully without errors or output with 5 200 200 200 2147483649

[~] Test #37 Program output multiple lines with 5 200 200 2147483649 5, you should decide if this case is handled well. Here are the last 2 lines:
 0 3 is eating
200 1 died 


		[============[ Error on Threads Creation ]==============]

[+] Test #38 Threads are protected during initialization agaisn't insufficient memory, no errors found 
*/