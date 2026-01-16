/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:43:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/16 15:53:59 by mperrine         ###   ########.fr       */
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

enum	e_eat_states {
	NONE,
	WANT,
	EATING,
};

enum	e_sides {
	LEFT = -1,
	RIGHT = 1,
};

typedef struct s_philo
{
	pthread_t		thread;
	int				*dead;
	int				nb;
	int				nb_eaten;
	int				nb_to_eat;
	int				eat_status;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_last_meal;
	size_t			start_time;
	pthread_mutex_t	state;
	pthread_mutex_t	*print;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_prog
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				any_dead;
	int				nb_philos;
}	t_prog;



size_t	get_number(const char *nptr);
int		init_philos_data(t_prog *prog, int ac, char **av);
int		start_threads(t_prog *prog);
void	*philo_routine(void *arg);
size_t	get_time(t_philo *philo);
void	print(t_philo *philo, const char *s);
#endif
