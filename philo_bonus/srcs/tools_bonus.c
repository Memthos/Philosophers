/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 13:40:15 by mperrine         ###   ########.fr       */
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

void	basic_print(t_prog *prog, int nb, const char *s)
{
	size_t	time;

	sem_wait(prog->print);
	write(2, "TEST\n", 5);
	time = get_sim_time(prog);
	printf("%zu %d %s\n", time, nb, s);
	sem_post(prog->print);
}
