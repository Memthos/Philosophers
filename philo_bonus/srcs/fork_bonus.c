/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:20:24 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 14:31:12 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	routine(t_prog *prog)
{
	if (prog->data.nb % 2)
		ft_usleep(1);
	while (1)
	{
		sem_wait(prog->forks);
		basic_print(prog, prog->data.nb, "has taken a fork");
		sem_wait(prog->forks);
		basic_print(prog, prog->data.nb, "has taken a fork");
		prog->data.time_last_meal = get_sim_time(prog);
		prog->data.nb_eaten++;
		if (prog->data.nb_eaten == prog->data.nb_to_eat)
			sem_post(prog->eaten);
		basic_print(prog, prog->data.nb, "is eating");
		ft_usleep(prog->data.time_to_eat);
		sem_post(prog->forks);
		sem_post(prog->forks);
		basic_print(prog, prog->data.nb, "is sleeping");
		ft_usleep(prog->data.time_to_sleep);
		basic_print(prog, prog->data.nb, "is thinking");
	}
	exit(0);
}

void	kill_childs(t_prog *prog, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		kill(prog->childs[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		waitpid(prog->childs[i], NULL, 0);
		i++;
	}
	free(prog->childs);
	sem_close(prog->forks);
	sem_close(prog->stop);
	sem_close(prog->eaten);
	sem_close(prog->print);
}

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
