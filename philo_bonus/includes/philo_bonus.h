/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:43:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 17:09:18 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <signal.h>
# include <string.h>

typedef struct s_data
{
	int				nb;
	size_t			nb_eaten;
	size_t			nb_to_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_last_meal;
	size_t			start_time;
}	t_data;

typedef struct s_prog
{
	pid_t	*childs;
	sem_t	*forks;
	sem_t	*stop;
	sem_t	*kill;
	sem_t	*eaten;
	sem_t	*print;
	sem_t	*meal;
	t_data	data;
	int		nb_philos;
}	t_prog;

int		start_childs(t_prog *prog);

void	*eaten_enough(void *arg);
void	*is_starving(void *arg);
void	*kill_check(void *arg);

void	kill_childs(t_prog *prog, int nb);

size_t	get_number(const char *nptr);
void	basic_print(t_prog *prog, const char *s);

size_t	get_current_time(void);
void	ft_usleep(size_t time);
size_t	get_sim_time(t_prog *prog);

#endif
