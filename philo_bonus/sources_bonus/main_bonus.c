/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:41:16 by revieira          #+#    #+#             */
/*   Updated: 2023/05/15 17:06:23 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	free_struct(t_philo *philo)
{
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	sem_close(philo->forks_in_table);
	sem_close(philo->on_print);
	free(philo);
}

void	wait_for_childs_processes(int *pid, t_philo *philo)
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
	if (status)
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

int	only_one_philo(t_philo *philo)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		sem_post(philo->forks_in_table);
		print_action(philo, TAKEN_FORK);
		usleep(philo->data->time_to_die * 1000);
		print_action(philo, DIED);
		sem_wait(philo->forks_in_table);
		free_struct(philo);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	free_struct(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo *philosophers;

	if (!check_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	philosophers = init_philosophers(&data);
	if (data.nbr_of_philos == 1)
		return(only_one_philo(philosophers));
	create_child_processes(philosophers);
	free_struct(philosophers);
	return (0);
}
