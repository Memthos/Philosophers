/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:57:31 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/26 18:49:14 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	start_childs(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philos)
	{
		prog->childs[i] = fork();
		if (prog->childs[i] == -1)
		{
			kill_childs(prog, i);
			return (1);
		}
		else if (prog->childs[i] == 0)
		{
			prog->data.nb = i + 1;
			free(prog->childs);
			routine(prog);
		}
		i++;
	}
	return (0);
}

static int	init_semaphores(t_prog *prog)
{
	sem_unlink("forks");
	sem_unlink("global_stop");
	sem_unlink("kill_childs");
	sem_unlink("kill_check");
	sem_unlink("eat_counter");
	sem_unlink("print_lock");
	sem_unlink("meal_lock");
	prog->forks = sem_open("forks", O_CREAT, 0666, prog->nb_philos);
	prog->global_stop = sem_open("global_stop", O_CREAT, 0666, 0);
	prog->kill_childs = sem_open("kill_childs", O_CREAT, 0666, 0);
	prog->kill_check = sem_open("kill_check", O_CREAT, 0666, 1);
	prog->eat_counter = sem_open("eat_counter", O_CREAT, 0666, 0);
	prog->print_lock = sem_open("print_lock", O_CREAT, 0666, 1);
	prog->meal_lock = sem_open("meal_lock", O_CREAT, 0666, 1);
	if (prog->forks == SEM_FAILED || prog->global_stop == SEM_FAILED
		|| prog->eat_counter == SEM_FAILED || prog->print_lock == SEM_FAILED
		|| prog->kill_childs == SEM_FAILED || prog->meal_lock == SEM_FAILED
		|| prog->kill_check == SEM_FAILED)
		return (1);
	return (0);
}

static size_t	get_number(const char *nptr)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		if (res > ((((size_t) - 1) - (nptr[i] - '0')) / 10))
			return (0);
		res = (res * 10) + (nptr[i++] - '0');
	}
	return (res);
}

t_prog	init_data(int ac, char **av)
{
	t_prog	prog;

	prog.nb_philos = get_number(av[0]);
	prog.data = (t_data){0, 0, 0, 0, get_number(av[1]), get_number(av[2]),
		get_number(av[3]), 0, get_current_time()};
	if (ac == 5)
		prog.data.nb_to_eat = get_number(av[4]);
	if (init_semaphores(&prog))
	{
		close_semaphores(&prog);
		exit(1);
	}
	prog.childs = malloc(sizeof(pid_t) * prog.nb_philos);
	if (!prog.childs)
	{
		close_semaphores(&prog);
		exit(1);
	}
	return (prog);
}

int	check_inputs(int ac, char **av)
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
