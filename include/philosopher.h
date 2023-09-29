/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:28:29 by uclement          #+#    #+#             */
/*   Updated: 2023/09/29 22:58:06 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <inttypes.h>
# include "libft.h"
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data {
	int				count;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	loop;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo {
	int				id;
	u_int64_t		ttdie;
	u_int64_t		tteat;
	u_int64_t		ttsleep;
	int				count;
	int				count_meal;
	int				is_eating;
	int				must_eat;
	int				dead;
	u_int64_t		lastmeal;
	u_int64_t		start;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	meal;
	t_data			*data;
}	t_philo;



//init
void	init_all(t_data *data, t_philo *philo, pthread_mutex_t *forks, char **av);
void	init_forks(pthread_mutex_t *forks, char nb_philo);
void	init_philo(t_philo *philo, pthread_mutex_t *forks, char **av, t_data *data);
void	init_data(t_data *data, int count);

//utils
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

//process
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*routine(void *philo_ptr);
void	print_txt(t_philo *philo, char *str);
void	philo_think(t_philo *philo);

//threads
void	threads_maker(t_philo *philo);

void is_philo_dead(t_philo *philo);

#endif