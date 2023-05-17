/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:56:19 by revieira          #+#    #+#             */
/*   Updated: 2023/05/17 12:17:16 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

static void	wait_for_childs_processes(int *pid_array, t_philo *philo)
{
	int	i;
	int	pid;
	int	status;

	i = 0;
	status = 0;
	while (i < philo->data->nbr_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
			break ;
		i++;
	}
	if (WEXITSTATUS(status) == 1)
	{
		i = 0;
		while (i < philo->data->nbr_of_philos)
		{
			pid = pid_array[i];
			kill(pid, SIGKILL);
			i++;
		}
	}
}

void	create_child_processes(t_philo *philo)
{
	int	i;
	int	*pid;

	i = 0;
	pid = malloc(sizeof(int) * philo->data->nbr_of_philos);
	while (i < philo->data->nbr_of_philos)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			routine(&philo[i]);
		i++;
	}
	wait_for_childs_processes(pid, philo);
	free(pid);
}
