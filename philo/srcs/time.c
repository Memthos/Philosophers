/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:08:10 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 17:09:02 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_current_time(void)
{
	size_t			time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

void	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < time)
	{
		if (philo && should_stop(philo))
			return ;
		usleep(500);
	}
}

size_t	get_sim_time(t_philo *philo)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	return (time);
}
