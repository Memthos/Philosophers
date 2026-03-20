/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:36:04 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/20 16:28:31 by mperrine         ###   ########.fr       */
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
	printf("%zu %d %s\n", time, philo->nb, s);
	pthread_mutex_unlock(philo->print_lock);
}

static int	contain_char(char **s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] < '0' || s[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_inputs(int ac, char **av)
{
	int	ret;

	ret = 0;
	if (ac != 4 && ac != 5)
		ret = 1;
	if (!ret && (get_number(av[0]) < 1 || get_number(av[0]) > 200))
		ret = 1;
	if (!ret && (contain_char(av)))
		ret = 1;
	if (ret)
		printf("Wrong arguments\n");
	return (ret);
}
