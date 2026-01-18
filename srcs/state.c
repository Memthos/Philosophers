/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:08:36 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/18 22:11:48 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_dead(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(philo->dead_lock);
	res = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (res);
}

int	eaten_enough(t_philo *philo)
{
	int	res;

	res = 1;
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->nb_to_eat == -1 || philo->nb_eaten < philo->nb_to_eat)
		res = 0;
	pthread_mutex_unlock(&philo->eat_lock);
	return (res);
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
