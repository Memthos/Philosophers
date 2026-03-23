/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 18:48:11 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_number(const char *nptr)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		if (res > ((((size_t) - 1) - (nptr[i] - '0')) / 10))
			return (0);
		res = (res * 10) + (nptr[i++] - '0');
	}
	return (res);
}

void	check_print(t_philo *philo, const char *s)
{
	if (should_stop(philo))
		return ;
	basic_print(philo, s);
}

void	basic_print(t_philo *philo, const char *s)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_sim_time(philo);
	printf("%zu %d %s\n", time, philo->nb, s);
	pthread_mutex_unlock(philo->print_lock);
}

int	check_inputs(int ac, char **av)
{
	int	ret;
	int	i;
	int	j;

	ret = 0;
	if (ac != 4 && ac != 5)
		ret = 1;
	i = 0;
	while (!ret && av[i])
	{
		j = 0;
		while (!ret && av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				ret = 1;
			j++;
		}
		if (!ret && get_number(av[i++]) < 1)
			ret = 1;
	}
	if (!ret && get_number(av[0]) > 200)
		ret = 1;
	if (ret)
		write(2, "Wrong arguments\n", 16);
	return (ret);
}
