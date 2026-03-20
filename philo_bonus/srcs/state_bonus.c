/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:08:36 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/20 19:20:52 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	should_stop(t_prog *prog)
{
	return (0);
}

int	eaten_enough(t_prog *prog)
{
	int		res;
	size_t	nb_to_eat;
	int		i;

	pthread_mutex_lock(&prog->philos[0].eat_lock);
	nb_to_eat = prog->philos[0].nb_to_eat;
	pthread_mutex_unlock(&prog->philos[0].eat_lock);
	if (nb_to_eat == 0)
		return (0);
	i = -1;
	res = 0;
	while (++i < prog->nb_philos)
	{
		pthread_mutex_lock(&prog->philos[i].eat_lock);
		if (prog->philos[i].nb_eaten >= nb_to_eat)
			res++;
		pthread_mutex_unlock(&prog->philos[i].eat_lock);
	}
	if (res == prog->nb_philos)
		return (1);
	return (0);
}

int	is_starving(t_prog *prog)
{
	size_t	last_meal;

	last_meal = prog->data.time_last_meal;
	if (get_sim_time(prog) - last_meal >= prog->data.time_to_die)
		return (1);
	return (0);
}
