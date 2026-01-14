/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/14 13:32:20 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_forks(t_prog **prog)
{
	int	i;

	(*prog)->forks = malloc(sizeof(pthread_mutex_t *) * (*prog)->nb_philos);
	if (!(*prog)->forks)
		return (1);
	i = -1;
	while (++i < (*prog)->nb_philos)
		pthread_mutex_init((*prog)->forks[i], NULL);
}

static void	close(t_prog **prog)
{
	int	i;

	if ((*prog)->forks)
	{
		i = -1;
		while (++i < (*prog)->nb_philos)
		{
			pthread_mutex_destroy((*prog)->forks[i]);
			free((*prog)->forks[i]);
		}
	}
	if ((*prog)->philos)
	{
		i = -1;
		while (++i < (*prog)->nb_philos)
			free((*prog)->philos[i]);
	}
	free(*prog);
}

int	main(int ac, char **av)
{
	t_prog	*prog;

	if (ac != 5 || ac != 6)
		return (1);
	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (NULL);
	prog->any_dead = 0;
	prog->nb_philos = get_number(av[1]);
	if (init_forks(&prog) || init_philos_data(&prog, ac - 1, av + 1))
	{
		close(&prog);
		return (1);
	}
	start_threads(&prog);
	while (!prog->any_dead)
	{}
}
