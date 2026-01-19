/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:08:36 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/19 13:44:39 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	should_stop(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(philo->stop_lock);
	res = *philo->stop_flag;
	pthread_mutex_unlock(philo->stop_lock);
	return (res);
}

int	eaten_enough(t_prog *prog)
{
	int	res;
	int	nb_to_eat;
	int	i;

	pthread_mutex_lock(&prog->philos[0].eat_lock);
	nb_to_eat = prog->philos[0].nb_to_eat;
	pthread_mutex_unlock(&prog->philos[0].eat_lock);
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

int	is_starving(t_philo *philo)
{
	int		res;
	size_t	last_meal;

	res = 0;
	pthread_mutex_lock(&philo->eat_lock);
	last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->eat_lock);
	if (get_sim_time(philo) - last_meal >= philo->time_to_die)
		res = 1;
	return (res);
}
