/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:37:03 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/30 11:23:25 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	lock_forks(t_philo *philo)
{
	if (philo->l_fork < philo->r_fork)
	{
		pthread_mutex_lock(philo->l_fork);
		check_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		check_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		check_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		check_print(philo, "has taken a fork");
	}
}

static void	unlock_forks(t_philo *philo)
{
	if (philo->l_fork < philo->r_fork)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

static void	one_philo_routine(t_philo *philo)
{
	check_print(philo, "has taken a fork");
	ft_usleep(philo->time_to_die + 1, philo);
}

void	think(t_philo *philo)
{
	long	time;

	time = philo->time_to_die - philo->time_to_eat - philo->time_to_sleep - 10;
	if (time < 0)
		time = 0;
	else if (time > 600)
		time = 200;
	ft_usleep((size_t)time / 2, philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->l_fork == philo->r_fork)
		one_philo_routine(philo);
	if (philo->nb % 2 == 0)
		ft_usleep(philo->time_to_eat / 2, philo);
	while (!should_stop(philo))
	{
		lock_forks(philo);
		pthread_mutex_lock(&philo->eat_lock);
		philo->time_last_meal = get_sim_time(philo);
		philo->nb_eaten++;
		pthread_mutex_unlock(&philo->eat_lock);
		check_print(philo, "is eating");
		ft_usleep(philo->time_to_eat, philo);
		unlock_forks(philo);
		check_print(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep, philo);
		check_print(philo, "is thinking");
		think(philo);
	}
	return (0);
}
