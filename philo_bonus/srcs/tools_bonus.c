/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 23:53:02 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	safe_print(t_prog *prog, const char *s, int bypass)
{
	size_t	time;

	if (bypass == 0)
	{
		sem_wait(prog->kill_check);
		if (prog->data.kill == 1)
		{
			sem_post(prog->kill_check);
			return ;
		}
	}
	sem_post(prog->kill_check);
	sem_wait(prog->print_lock);
	time = get_sim_time(prog);
	printf("%zu %d %s\n", time, prog->data.nb, s);
	sem_post(prog->print_lock);
}
