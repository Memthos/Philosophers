/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 18:24:36 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	observer(t_prog *prog)
{
	pthread_t	eat_thread;

	if (prog->data.nb_to_eat != 0)
	{
		if (pthread_create(&eat_thread, NULL, &eaten_enough, prog) != 0)
		{
			kill_childs(prog, prog->nb_philos);
			return ;
		}
	}
	else
		eat_thread = 0;
	sem_wait(prog->global_stop);
	kill_childs(prog, prog->nb_philos);
	if (eat_thread)
		pthread_join(eat_thread, NULL);
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
