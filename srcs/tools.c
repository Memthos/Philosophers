/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/17 18:52:09 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_number(const char *nptr)
{
	int		i;
	size_t	res;

	i = 0;
	res = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res *= 10;
		res += nptr[i] - 48;
		i++;
	}
	return (res);
}

size_t	get_time(t_philo *philo)
{
	struct timeval	t;
	size_t			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000) - philo->start_time;
	return (time);
}


void	print(t_philo *philo, const char *s)
{
	size_t	time;

	pthread_mutex_lock(philo->printf_lock);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->printf_lock);
		return ;
	}
	time = get_time(philo);
	printf("%lu %d %s\n", time, philo->nb, s);
	pthread_mutex_unlock(philo->printf_lock);
}

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
	int	res;
	size_t	last_meal;

	res = 0;
	pthread_mutex_lock(&philo->eat_lock);
	last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->eat_lock);
	if (get_time(philo) - last_meal >= philo->time_to_die)
		res = 1;
	return (res);
}

void	thread_join(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->nb_philos)
		pthread_join(prog->philos[i].thread, NULL);
}
