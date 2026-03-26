/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/26 18:46:24 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	pthread_mutex_destroy(&prog->stop_lock);
	pthread_mutex_destroy(&prog->print_lock);
}

static void	stop_sim(t_prog *prog)
{
	pthread_mutex_lock(&prog->stop_lock);
	prog->stop_flag = 1;
	pthread_mutex_unlock(&prog->stop_lock);
}

static void	observer(t_prog *prog)
{
	int		i;
	int		res;

	res = 0;
	while (!res)
	{
		i = -1;
		while (++i < prog->nb_philos)
		{
			if (is_starving(&prog->philos[i]))
			{
				stop_sim(prog);
				basic_print(&prog->philos[i], "died");
				res = 1;
				break ;
			}
			if (eaten_enough(prog))
			{
				stop_sim(prog);
				res = 1;
				break ;
			}
		}
		ft_usleep(1, NULL);
	}
}

static int	init_philos_data(t_prog *prog, int ac, char **av)
{
	int	i;

	prog->philos = malloc(sizeof(t_philo) * prog->nb_philos);
	if (!prog->philos)
		return (1);
	i = -1;
	while (++i < prog->nb_philos)
	{
		prog->philos[i].stop_flag = &prog->stop_flag;
		prog->philos[i].nb = i + 1;
		prog->philos[i].nb_eaten = 0;
		prog->philos[i].nb_to_eat = 0;
		if (ac == 5)
			prog->philos[i].nb_to_eat = get_number(av[4]);
		prog->philos[i].time_to_die = get_number(av[1]);
		prog->philos[i].time_to_eat = get_number(av[2]);
		prog->philos[i].time_to_sleep = get_number(av[3]);
		prog->philos[i].time_last_meal = 0;
		prog->philos[i].stop_lock = &prog->stop_lock;
		prog->philos[i].print_lock = &prog->print_lock;
		prog->philos[i].l_fork = &prog->forks[i];
		prog->philos[i].r_fork = &prog->forks[(i + 1) % prog->nb_philos];
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_prog	prog;
	int		ret;

	ret = 0;
	if (check_inputs(ac - 1, av + 1))
		return (1);
	prog.forks = NULL;
	prog.nb_philos = get_number(av[1]);
	prog.philos = NULL;
	prog.stop_flag = 0;
	if (pthread_mutex_init(&prog.stop_lock, NULL))
		ret = 1;
	if (!ret && pthread_mutex_init(&prog.print_lock, NULL))
		ret = 1;
	if (!ret && (init_forks(&prog) || init_philos_data(&prog, ac - 1, av + 1)))
		ret = 1;
	if (!ret && start_threads(&prog))
		ret = 1;
	if (!ret)
	{
		observer(&prog);
		thread_join(&prog);
	}
	close_philo(&prog);
	return (ret);
}
