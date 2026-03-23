/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:20:24 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 18:33:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	routine_actions(t_prog *prog)
{
	while (!should_stop(prog))
	{
		sem_wait(prog->forks);
		safe_print(prog, "has taken a fork");
		sem_wait(prog->forks);
		safe_print(prog, "has taken a fork");
		sem_wait(prog->meal_lock);
		prog->data.time_last_meal = get_sim_time(prog);
		prog->data.nb_eaten++;
		sem_post(prog->meal_lock);
		if (prog->data.nb_eaten == prog->data.nb_to_eat)
			sem_post(prog->eat_counter);
		safe_print(prog, "is eating");
		ft_usleep(prog->data.time_to_eat, prog);
		sem_post(prog->forks);
		sem_post(prog->forks);
		safe_print(prog, "is sleeping");
		ft_usleep(prog->data.time_to_sleep, prog);
		safe_print(prog, "is thinking");
	}
}

static void	routine(t_prog *prog)
{
	pthread_t	kill_thread;
	pthread_t	starve_thread;

	if (pthread_create(&kill_thread, NULL, &kill_state, prog) != 0)
		exit(0);
	if (pthread_create(&starve_thread, NULL, &is_starving, prog) != 0)
		sem_post(prog->global_stop);
	if (prog->data.nb % 2)
		ft_usleep(1, prog);
	routine_actions(prog);
	pthread_join(kill_thread, NULL);
	pthread_join(starve_thread, NULL);
	close_semaphores(prog);
	exit(0);
}

void	close_semaphores(t_prog *prog)
{
	if (prog->forks != SEM_FAILED)
		sem_close(prog->forks);
	if (prog->global_stop != SEM_FAILED)
		sem_close(prog->global_stop);
	if (prog->kill_childs != SEM_FAILED)
		sem_close(prog->kill_childs);
	if (prog->kill_check != SEM_FAILED)
		sem_close(prog->kill_check);
	if (prog->eat_counter != SEM_FAILED)
		sem_close(prog->eat_counter);
	if (prog->print_lock != SEM_FAILED)
		sem_close(prog->print_lock);
	if (prog->meal_lock != SEM_FAILED)
		sem_close(prog->meal_lock);
}

void	kill_childs(t_prog *prog, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		sem_post(prog->kill_childs);
		sem_post(prog->eat_counter);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		waitpid(prog->childs[i], NULL, 0);
		i++;
	}
	free(prog->childs);
	close_semaphores(prog);
}

int	start_childs(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->nb_philos)
	{
		prog->childs[i] = fork();
		if (prog->childs[i] == -1)
		{
			kill_childs(prog, i);
			return (1);
		}
		else if (prog->childs[i] == 0)
		{
			prog->data.nb = i + 1;
			free(prog->childs);
			routine(prog);
		}
		i++;
	}
	return (0);
}
