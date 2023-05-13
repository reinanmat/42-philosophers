/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:41:16 by revieira          #+#    #+#             */
/*   Updated: 2023/05/13 18:23:57 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	free_struct(t_philo *philo)
{
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	sem_close(philo->table->forks_in_table);
	free(philo->table);
	free(philo);
}

void	in_child(t_philo *philo)
{
	pthread_t	th;

	philo->last_meal = get_time();
	pthread_create(&th, NULL, &routine, (void *)philo);
	while (1)
	{
		usleep(500);
		if (get_time() - philo->last_meal > philo->data->time_to_die)
		{
			philo->status = 0;
			break ;
		}
	}
	pthread_join(th, NULL);
	free_struct(philo);
	exit(1);
}

void	create_child_processes(t_philo *philo)
{
	int	i;
	int	pid;

	i = 0;
	while (i < philo->data->nbr_of_philos)
	{
		pid = fork();
		if (pid == 0)
			in_child(&philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->data->nbr_of_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	return (0);
}
