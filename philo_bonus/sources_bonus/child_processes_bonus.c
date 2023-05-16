/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:56:19 by revieira          #+#    #+#             */
/*   Updated: 2023/05/16 17:38:47 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

static void	wait_for_childs_processes(int *pid, t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < philo->data->nbr_of_philos && WEXITSTATUS(status) == 0)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WEXITSTATUS(status) == 1)
	{
		i = 0;
		while (i < philo->data->nbr_of_philos)
		{
			kill(pid[i], SIGKILL);
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
