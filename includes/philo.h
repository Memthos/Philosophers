/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:43:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/21 19:20:52 by mperrine         ###   ########.fr       */
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
	int				*stop_flag;
	int				nb;
	size_t			nb_eaten;
	size_t			nb_to_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_last_meal;
	size_t			start_time;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*stop_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_prog
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	int				stop_flag;
	int				nb_philos;
}	t_prog;

int		check_inputs(int ac, char **av);
size_t	get_number(const char *nptr);
int		init_forks(t_prog *prog);
int		init_philos_data(t_prog *prog, int ac, char **av);
int		start_threads(t_prog *prog);
void	*philo_routine(void *arg);
void	thread_join(t_prog *prog);
void	check_print(t_philo *philo, const char *s);
void	basic_print(t_philo *philo, const char *s);
int		should_stop(t_philo *philo);
int		eaten_enough(t_prog *prog);
int		is_starving(t_philo *philo);
size_t	get_current_time(void);
void	ft_usleep(size_t time);
size_t	get_sim_time(t_philo *philo);

#endif
