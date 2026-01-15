/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/15 14:42:30 by mperrine         ###   ########.fr       */
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

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	printf("%lu %d has taken a fork\n", get_time(philo), philo->nb);
	pthread_mutex_lock(philo->r_fork);
	printf("%lu %d has taken a fork\n", get_time(philo), philo->nb);
}

int	can_lock_forks(t_prog *prog, int index)
{
	int	left_nb;
	int	right_nb;

	if (prog->philos[index].nb == 1)
		left_nb = prog->nb_philos - 1;
	else
		left_nb = index - 1;
	if (index == prog->nb_philos - 1)
		right_nb = 0;
	else
		right_nb = index + 1;
	if (prog->philos[left_nb].can_eat || prog->philos[right_nb].can_eat)
		return (1);
	return (0);
}
