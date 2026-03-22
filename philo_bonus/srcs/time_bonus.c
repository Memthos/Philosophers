/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 22:08:10 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/22 11:11:53 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

size_t	get_current_time(void)
{
	size_t			time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

void	ft_usleep(size_t time, t_prog *prog)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < time)
	{
		if (should_stop(prog))
			return ;
		usleep(500);
	}
}

size_t	get_sim_time(t_prog *prog)
{
	size_t	time;

	time = get_current_time() - prog->data.start_time;
	return (time);
}
