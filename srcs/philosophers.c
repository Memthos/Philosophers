/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:37:03 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/18 22:27:52 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philos_data(t_prog *prog, int ac, char **av)
{
	int	i;

	prog->philos = malloc(sizeof(t_philo) * prog->nb_philos);
	if (!prog->philos)
		return (1);
	i = -1;
	while (++i < prog->nb_philos)
	{
		prog->philos[i].dead = &prog->any_dead;
		prog->philos[i].nb = i + 1;
		prog->philos[i].nb_eaten = 0;
		prog->philos[i].nb_to_eat = -1;
		if (ac == 5)
			prog->philos[i].nb_to_eat = get_number(av[4]);
		pthread_mutex_init(&prog->philos[i].eat_lock, NULL);
		prog->philos[i].time_to_die = get_number(av[1]);
		prog->philos[i].time_to_eat = get_number(av[2]);
		prog->philos[i].time_to_sleep = get_number(av[3]);
		prog->philos[i].time_last_meal = 0;
		prog->philos[i].dead_lock = &prog->death_lock;
		prog->philos[i].printf_lock = &prog->print_lock;
		prog->philos[i].l_fork = &prog->forks[i];
		prog->philos[i].r_fork = &prog->forks[(i + 1) % prog->nb_philos];
	}
	return (0);
}

int	start_threads(t_prog *prog)
{
	int				i;
	size_t			start_time;

	i = -1;
	start_time = get_current_time();
	while (++i < prog->nb_philos)
	{
		prog->philos[i].start_time = start_time;
		if (pthread_create(&prog->philos[i].thread, NULL,
				philo_routine, &prog->philos[i]) != 0)
			return (1);
	}
	return (0);
}

static void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print(philo, "has taken a fork");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->nb % 2)
		ft_usleep(1);
	while (!is_dead(philo))
	{
		lock_forks(philo);
		pthread_mutex_lock(&philo->eat_lock);
		philo->time_last_meal = get_sim_time(philo);
		philo->nb_eaten++;
		pthread_mutex_unlock(&philo->eat_lock);
		print(philo, "is eating");
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		print(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		print(philo, "is thinking");
	}
	return (0);
}
