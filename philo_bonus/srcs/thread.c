/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:20:24 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/21 17:46:04 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thread_join(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->nb_philos)
		pthread_join(prog->philos[i].thread, NULL);
}

int	start_threads(t_prog *prog)
{
	int				i;
	size_t			start_time;

	i = -1;
	start_time = get_current_time();
	while (++i < prog->nb_philos)
	{
		prog->philos[i].start_time = start_time;
		if (pthread_mutex_init(&prog->philos[i].eat_lock, NULL))
			return (1);
		if (pthread_create(&prog->philos[i].thread, NULL,
				philo_routine, &prog->philos[i]) != 0)
			return (1);
	}
	return (0);
}

int	init_forks(t_prog *prog)
{
	int	i;

	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->nb_philos);
	if (!prog->forks)
		return (1);
	i = -1;
	while (++i < prog->nb_philos)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL))
			return (1);
	}
	return (0);
}
