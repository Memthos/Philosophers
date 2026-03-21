/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:08:36 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 17:06:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*eaten_enough(void *arg)
{
	t_prog	*prog;
	int		i;

	prog = (t_prog *)arg;
	i = 0;
	while (i < prog->nb_philos)
	{
		sem_wait(prog->eaten);
		i++;
	}
	sem_post(prog->stop);
	return (0);
}

void	*is_starving(void *arg)
{
	t_prog	*prog;
	size_t	last_meal;

	prog = (t_prog *)arg;
	while (1)
	{
		sem_wait(prog->meal);
		last_meal = prog->data.time_last_meal;
		sem_post(prog->meal);
		if (get_sim_time(prog) - last_meal >= prog->data.time_to_die)
		{
			sem_post(prog->stop);
			basic_print(prog, "died");
			exit(0);
		}
		ft_usleep(1);
	}
	return (0);
}

void	*kill_check(void *arg)
{
	t_prog	*prog;

	prog = (t_prog *)arg;
	sem_wait(prog->kill);
	exit (0);
}
