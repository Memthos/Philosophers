/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/19 14:00:56 by mperrine         ###   ########.fr       */
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
	printf("%lu %d %s\n", time, philo->nb, s);
	pthread_mutex_unlock(philo->print_lock);
}

int	check_inputs(int ac, char **av)
{
	int	i;
	int	ret;

	ret = 0;
	if (ac != 4 && ac != 5)
		ret = 1;
	i = -1;
	if (get_number(av[++i]) < 1)
		ret = 1;
	while (!ret && ++i < ac)
	{
		if (get_number(av[i]) < 0)
			ret = 1;
	}
	if (ret)
		printf("Wrong arguments\n");
	return (ret);
}
