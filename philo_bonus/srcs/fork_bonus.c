/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:20:24 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 13:39:52 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	routine(t_prog *prog)
{
	if (prog->data.nb % 2)
		ft_usleep(1, prog);
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
		ft_usleep(prog->data.time_to_eat, prog);
		sem_post(prog->forks);
		sem_post(prog->forks);
		basic_print(prog, prog->data.nb, "is sleeping");
		ft_usleep(prog->data.time_to_sleep, prog);
		basic_print(prog, prog->data.nb, "is thinking");
	}
	free(prog->childs);
	exit(0);
}

void	kill_childs(pid_t *childs, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		kill(childs[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		waitpid(childs[i], NULL, 0);
		i++;
	}
	free(childs);

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
			kill_childs(prog->childs, i - 1);
			return (1);
		}
		else if (prog->childs[i] == 0)
		{
			prog->data.nb = i + 1;
			routine(prog);
		}
		i++;
	}
	return (0);
}
