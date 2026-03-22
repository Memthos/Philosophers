/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/22 11:26:07 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	safe_print(t_prog *prog, const char *s)
{
	size_t	time;

	sem_wait(prog->print_lock);
	if (should_stop(prog))
	{
		sem_post(prog->print_lock);
		return ;
	}
	time = get_sim_time(prog);
	printf("%zu %d %s\n", time, prog->data.nb, s);
	if (ft_strcmp((char *)s, "died") == 0)
		return ;
	sem_post(prog->print_lock);
}
