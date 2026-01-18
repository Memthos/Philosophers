/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/18 22:27:51 by mperrine         ###   ########.fr       */
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

static void	thread_join(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->nb_philos)
		pthread_join(prog->philos[i].thread, NULL);
}

static void	close_philo(t_prog *prog)
{
	int	i;

	if (prog->forks)
	{
		i = -1;
		while (++i < prog->nb_philos)
			pthread_mutex_destroy(&prog->forks[i]);
		free(prog->forks);
	}
	if (prog->philos)
	{
		i = -1;
		while (++i < prog->nb_philos)
			pthread_mutex_destroy(&prog->philos[i].eat_lock);
		free(prog->philos);
	}
	pthread_mutex_destroy(&prog->death_lock);
	pthread_mutex_destroy(&prog->print_lock);
}

static void	observer(t_prog *prog)
{
	int		i;
	int		res;
	size_t	time;

	res = 0;
	while (!res)
	{
		i = -1;
		while (++i < prog->nb_philos)
		{
			if (is_starving(&prog->philos[i]))
			{
				pthread_mutex_lock(prog->philos[i].dead_lock);
				*prog->philos[i].dead = 1;
				pthread_mutex_unlock(prog->philos[i].dead_lock);
				pthread_mutex_lock(prog->philos[i].printf_lock);
				time = get_sim_time(&prog->philos[i]);
				printf("%lu %d has died\n", time, prog->philos[i].nb);
				pthread_mutex_unlock(prog->philos[i].printf_lock);
				res = 1;
				break ;
			}
		}
		ft_usleep(1);
	}
}

int	main(int ac, char **av)
{
	t_prog	prog;

	if (ac != 5 && ac != 6)
		return (1);
	prog.any_dead = 0;
	prog.nb_philos = get_number(av[1]);
	pthread_mutex_init(&prog.death_lock, NULL);
	pthread_mutex_init(&prog.print_lock, NULL);
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
	thread_join(&prog);
	close_philo(&prog);
	return (0);
}
