/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:20:24 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/20 19:19:18 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	routine(t_prog *prog)
{
	if (prog->nb_philos == 1)
	{
		check_print(prog, "has taken a fork");
		ft_usleep(prog->data.time_to_die, prog);
	}
	if (prog->data.nb % 2)
		ft_usleep(1, prog);
	while (!should_stop(prog))
	{
		sem_wait(prog->sem);
		check_print(prog, "has taken a fork");
		sem_wait(prog->sem);
		check_print(prog, "has taken a fork");
		prog->data.time_last_meal = get_sim_time(prog);
		prog->data.nb_eaten++;
		check_print(prog, "is eating");
		ft_usleep(prog->data.time_to_eat, prog);
		sem_post(prog->sem);
		sem_post(prog->sem);
		check_print(prog, "is sleeping");
		ft_usleep(prog->data.time_to_sleep, prog);
		check_print(prog, "is thinking");
	}
	exit(0);
}

void	kill_childs(pid_t *childs, size_t nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		kill(childs[i], 1);
		i++;
	}
}

int	start_childs(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philos)
	{
		prog->childs[i] = fork();
		if (fork == -1)
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
