/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:43:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/17 18:47:57 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				*dead;
	int				nb;
	int				nb_eaten;
	int				nb_to_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_last_meal;
	size_t			start_time;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*printf_lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_prog
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	int				any_dead;
	int				nb_philos;
}	t_prog;



size_t	get_number(const char *nptr);
int		init_philos_data(t_prog *prog, int ac, char **av);
int		start_threads(t_prog *prog);
void	*philo_routine(void *arg);
size_t	get_time(t_philo *philo);
void	print(t_philo *philo, const char *s);
int		is_dead(t_philo *philo);
int		eaten_enough(t_philo *philo);
int		is_starving(t_philo *philo);
void	thread_join(t_prog *prog);

#endif
