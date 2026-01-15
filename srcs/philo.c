/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/15 14:56:35 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_forks(t_prog *prog)
{
	int	i;

	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->nb_philos);
	if (!prog->forks)
		return (1);
	i = -1;
	while (++i < prog->nb_philos)
		pthread_mutex_init(&prog->forks[i], NULL);
	return (0);
}

static void	close_philo(t_prog *prog)
{
	int	i;

	if (prog->forks)
	{
		i = -1;
		while (++i < prog->nb_philos)
		{
			pthread_mutex_destroy(&prog->forks[i]);
		}
		free(prog->forks);
	}
	if (prog->philos)
	{
		i = -1;
		while (++i < prog->nb_philos)
			free(&prog->philos[i]);
	}
}

static void	observer(t_prog *prog)
{
	int		i;
	t_philo	*philo_to_eat;

	while (!prog->any_dead)
	{
		i = -1;
		philo_to_eat = NULL;
		while (++i < prog->nb_philos)
		{
			if (prog->philos[i].wanna_eat
				&& !can_lock_forks(prog, i) && (!philo_to_eat
					|| prog->philos[i].nb_eaten < philo_to_eat->nb_eaten))
				philo_to_eat = &prog->philos[i];
		}
		if (philo_to_eat)
			philo_to_eat->can_eat = 1;
	}
}

int	main(int ac, char **av)
{
	t_prog	prog;

	if (ac != 5 && ac != 6)
		return (1);
	prog.any_dead = 0;
	prog.nb_philos = get_number(av[1]);
	if (init_forks(&prog) || init_philos_data(&prog, ac - 1, av + 1))
	{
		close_philo(&prog);
		return (1);
	}
	if (start_threads(&prog))
	{
		close_philo(&prog);
		return (1);
	}
	observer(&prog);
	close_philo(&prog);
	return (0);
}
