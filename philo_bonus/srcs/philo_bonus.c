/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/20 19:03:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

static t_prog	init_data(int ac, char **av)
{
	t_prog	prog;

	prog.nb_philos = get_number(av[0]);
	prog.sem = sem_open("forks", O_CREAT, 0666, prog.nb_philos);
	if (prog.sem == SEM_FAILED)
		exit(1);
	prog.childs = malloc(sizeof(pid_t) * prog.nb_philos);
	if (!prog.childs)
	{
		sem_unlink("forks");
		exit(1);
	}
	prog.data = (t_data){0, 0, 0, get_number(av[1]), get_number(av[2]),
		get_number(av[3]), get_current_time()};
	if (ac == 5)
		prog.data.nb_to_eat = get_number(av[4]);
	return (prog);
}

static int	check_inputs(int ac, char **av)
{
	int	ret;
	int	i;
	int	j;

	ret = 0;
	if (ac != 4 && ac != 5)
		ret = 1;
	i = 0;
	while (!ret && av[i])
	{
		j = 0;
		while (!ret && av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				ret = 1;
		}
		if (!ret && get_number(av[i++]) < 1)
			ret = 1;
	}
	if (!ret && get_number(av[0]) > 200)
		ret = 1;
	if (ret)
		write(2, "Wrong arguments\n", 16);
	return (ret);
}

int	main(int ac, char **av)
{
	t_prog	prog;

	if (check_inputs(ac - 1, av + 1))
		return (1);
	prog = init_data(ac, av);
	if (start_childs(&prog))
		return (1);
	observer(&prog);
	close_philo(&prog);
}
