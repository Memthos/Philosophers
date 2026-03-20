/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:43:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/20 19:21:22 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
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
	sem_t	*sem;
	t_data	data;
	int		nb_philos;
}	t_prog;

size_t	get_number(const char *nptr);
void	check_print(t_prog *philo, const char *s);
void	basic_print(t_prog *philo, const char *s);

int		should_stop(t_prog *prog);
int		eaten_enough(t_prog *prog);
int		is_starving(t_prog *philo);

size_t	get_current_time(void);
void	ft_usleep(size_t time, t_prog *prog);
size_t	get_sim_time(t_prog *prog);

#endif
