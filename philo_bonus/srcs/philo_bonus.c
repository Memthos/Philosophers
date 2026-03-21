/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 14:07:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	observer(t_prog *prog)
{
	int			ret;
	pthread_t	eat_thread;
	pthread_t	stop_thread;

	ret = 0;
	if (prog->data.nb_to_eat != 0)
	{
		if (pthread_create(&eat_thread, NULL, &eaten_enough, prog) != 0)
			ret = 1;
	}
	if (!ret && pthread_create(&stop_thread, NULL, &is_starving, prog) != 0)
	{
		pthread_join(eat_thread, NULL);
		ret = 1;
	}
	if (ret == 0)
	{
		sem_wait(prog->stop);
		sem_wait(prog->print);
		if (prog->data.nb_to_eat != 0)
			pthread_join(eat_thread, NULL);
		pthread_join(stop_thread, NULL);
	}
	kill_childs(prog, prog->nb_philos);
}

static void	init_semaphores(t_prog *prog)
{
	prog->forks = sem_open("forks", O_CREAT, 0666, prog->nb_philos);
	if (prog->forks == SEM_FAILED)
		exit(1);
	prog->stop = sem_open("stop", O_CREAT, 0666, 0);
	if (prog->stop == SEM_FAILED)
	{
		sem_close(prog->forks);
		exit(1);
	}
	prog->eaten = sem_open("eaten", O_CREAT, 0666, 0);
	if (prog->eaten == SEM_FAILED)
	{
		sem_close(prog->forks);
		sem_close(prog->stop);
		exit(1);
	}
	prog->print = sem_open("print", O_CREAT, 0666, 1);
	if (prog->print == SEM_FAILED)
	{
		sem_close(prog->forks);
		sem_close(prog->stop);
		sem_close(prog->eaten);
		exit(1);
	}
}

static t_prog	init_data(int ac, char **av)
{
	t_prog	prog;

	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("eaten");
	sem_unlink("print");
	prog.nb_philos = get_number(av[0]);
	init_semaphores(&prog);
	prog.childs = malloc(sizeof(pid_t) * prog.nb_philos);
	if (!prog.childs)
		exit(1);
	prog.data = (t_data){0, 0, 0, get_number(av[1]), get_number(av[2]),
		get_number(av[3]), 0, get_current_time()};
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
			j++;
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
	prog = init_data(ac - 1, av + 1);
	if (start_childs(&prog))
		return (1);
	observer(&prog);
}
