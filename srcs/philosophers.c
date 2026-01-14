/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:37:03 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/14 13:32:20 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	forks_pointers(t_prog **prog, int i)
{
	if (i == 0)
		(*prog)->philos[i]->l_fork = &(*prog)->forks[(*prog)->nb_philos - 1];
	else
		(*prog)->philos[i]->l_fork = &(*prog)->forks[i];
	if (i == (*prog)->nb_philos)
		(*prog)->philos[i]->r_fork = &(*prog)->forks[0];
	else
		(*prog)->philos[i]->r_fork = &(*prog)->forks[i];
}

int	init_philos_data(t_prog **prog, int ac, char **av)
{
	int	i;

	(*prog)->philos = malloc(sizeof(t_philo *) * (*prog)->nb_philos);
	if (!(*prog)->philos)
		return (1);
	i = -1;
	while (++i < (*prog)->nb_philos)
	{
		(*prog)->philos[i]->dead = &(*prog)->any_dead;
		(*prog)->philos[i]->nb = i + 1;
		(*prog)->philos[i]->nb_eaten = 0;
		if (ac == 5)
			(*prog)->philos[i]->nb_to_eat = get_number(av[4]);
		else
			(*prog)->philos[i]->nb_to_eat = -1;
		(*prog)->philos[i]->wanna_eat = 0;
		(*prog)->philos[i]->can_eat = 0;
		(*prog)->philos[i]->time_to_die = get_number(av[1]);
		(*prog)->philos[i]->time_to_eat = get_number(av[2]);
		(*prog)->philos[i]->time_to_sleep = get_number(av[3]);
		(*prog)->philos[i]->time_last_meal = 0;
		forks_pointers(prog, i);
	}
}

int	start_threads(t_prog **prog)
{
	int				i;
	struct timeval	t;

	i = -1;
	while (++i < (*prog)->nb_philos)
	{
		gettimeofday(&t, NULL);
		(*prog)->philos[i]->start_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		if (pthread_create(&(*prog)->philos[i]->thread, NULL,
				philo_routine, &(*prog)->philos[i]) != 0)
			return (1);
	}
}

void	philo_routine(t_philo **philo)
{
	while (!(*philo)->dead)
	{
		(*philo)->wanna_eat = 1;
		while (!(*philo)->can_eat)
		{
			if ((*philo)->time_last_meal >= (*philo)->time_to_die)
			(*philo)->dead = 1;
			usleep(100);
		}
		(*philo)->wanna_eat = 0;
		printf("%lu %d is eating\n", get_time(philo), (*philo)->nb);
		usleep((*philo)->time_to_eat * 1000);
		(*philo)->time_last_meal = get_time(philo);
		pthread_mutex_unlock((*philo)->l_fork);
		pthread_mutex_unlock((*philo)->r_fork);
		(*philo)->nb_eaten++;
		(*philo)->can_eat = 0;
		printf("%lu %d is sleeping\n", get_time(philo), (*philo)->nb);
		usleep((*philo)->time_to_sleep * 1000);
		printf("%lu %d is thinking\n", get_time(philo), (*philo)->nb);
	}
	printf("%lu %d has died\n", get_time(philo), (*philo)->nb);
}
