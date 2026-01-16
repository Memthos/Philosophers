/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/16 15:48:28 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_number(const char *nptr)
{
	int		i;
	size_t	res;

	i = 0;
	res = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res *= 10;
		res += nptr[i] - 48;
		i++;
	}
	return (res);
}

size_t	get_time(t_philo *philo)
{
	struct timeval	t;
	size_t			time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000) - philo->start_time;
	return (time);
}


void	print(t_philo *philo, const char *s)
{
	size_t	time;

	pthread_mutex_lock(&philo->print);
	time = get_time(philo);
	printf("%lu %d %s\n", time, philo->nb, s);
	pthread_mutex_unlock(&philo->print);
}
