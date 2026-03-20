/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/20 19:15:30 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

size_t	get_number(const char *nptr)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		if (res > ((((size_t) -1) - (nptr[i] - '0')) / 10))
			return (0);
		res = (res * 10) + (nptr[i++] - '0');
	}
	return (res);
}

void	check_print(t_prog *prog, const char *s)
{
	if (should_stop(prog))
		return ;
	basic_print(prog, s);
}

void	basic_print(t_prog *prog, const char *s)
{
	size_t	time;

	time = get_sim_time(prog);
	printf("%zu %d %s\n", time, prog->data.nb, s);
}
