/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:03:09 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/13 16:46:25 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine(t_philo *philo)
{}

static int	init_forks(t_program **prog)
{
	int		i;

	(*prog)->forks	= malloc(sizeof(pthread_mutex_t *) * (*prog)->nb_philos);
	if (!(*prog)->forks)
		return (1);
	i = -1;
	while (++i < (*prog)->nb_philos)
		pthread_mutex_init((*prog)->forks[i], NULL);
}

static int	init_philos(t_program **prog)
{
	int		i;

	(*prog)->philos	= malloc(sizeof(t_philo *) * (*prog)->nb_philos);
	if (!(*prog)->philos)
		return (1);
	i = -1;
	while (++i < (*prog)->nb_philos)
		pthread_create(&(*prog)->philos[i]->thread, NULL,
		routine, (*prog)->philos[i]);
}

void	close(t_program **prog)
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
	t_program	*prog;

	if (ac != 5 || ac != 6)
		return (1);
	prog = malloc(sizeof(t_program));
	if (!prog)
		return (NULL);
	prog->nb_philos = get_number(av[2]);
	if (init_forks(&prog) || init_philos(&prog))
	{
		close(&prog);
		return (1);
	}
}
