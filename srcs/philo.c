/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/19 13:30:56 by mperrine         ###   ########.fr       */
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
				basic_print(&prog->philos[i], "has died");
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
		ft_usleep(1);
	}
}

int	main(int ac, char **av)
{
	t_prog	prog;

	if (check_inputs(ac - 1, av + 1))
		return (1);
	prog.stop_flag = 0;
	prog.nb_philos = get_number(av[1]);
	pthread_mutex_init(&prog.stop_lock, NULL);
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
