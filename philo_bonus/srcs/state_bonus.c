/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:08:36 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/22 11:38:29 by mperrine         ###   ########.fr       */
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
		sem_wait(prog->eat_counter);
		i++;
	}
	sem_post(prog->global_stop);
	return (0);
}

void	*is_starving(void *arg)
{
	t_prog	*prog;
	size_t	last_meal;

	prog = (t_prog *)arg;
	while (!should_stop(prog))
	{
		sem_wait(prog->meal_lock);
		last_meal = prog->data.time_last_meal;
		sem_post(prog->meal_lock);
		if (get_sim_time(prog) - last_meal >= prog->data.time_to_die)
		{
			safe_print(prog, "died");
			sem_post(prog->global_stop);
			break ;
		}
		ft_usleep(1, prog);
	}
	return (0);
}

void	*kill_state(void *arg)
{
	t_prog	*prog;

	prog = (t_prog *)arg;
	sem_wait(prog->kill_childs);
	sem_wait(prog->kill_check);
	prog->data.kill = 1;
	sem_post(prog->kill_check);
	sem_post(prog->forks);
	sem_post(prog->forks);
	return (0);
}

int	should_stop(t_prog *prog)
{
	int	ret;

	ret = 0;
	sem_wait(prog->kill_check);
	if (prog->data.kill == 1)
		ret = 1;
	sem_post(prog->kill_check);
	return (ret);
}
