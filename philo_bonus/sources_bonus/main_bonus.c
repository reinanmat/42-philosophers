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

void	print_action(t_philo *philo, char *action)
{
	sem_wait(philo->on_print);
	printf("%ld	%d %s\n", get_timestamp(philo), philo->id, action);
	sem_post(philo->on_print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id & 1) == 0)
		usleep(500);
	while (philo->status)
	{
		sem_wait(philo->fork_left);
		print_action(philo, TAKEN_FORK);
		sem_wait(philo->fork_right);
		print_action(philo, TAKEN_FORK);
		print_action(philo, EAT);
		usleep(philo->data->time_to_eat * 1000);
		philo->last_meal = get_time();
		philo->meals++;
		sem_post(philo->fork_left);
		sem_post(philo->fork_right);
		print_action(philo, SLEEP);
		usleep(philo->data->time_to_sleep * 1000);
		print_action(philo, THINK);
		usleep(500);
	}
	return (NULL);
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
	t_philo *philosophers;
	t_data	data;

	if (!check_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	philosophers = init_philosophers(&data);
	create_child_processes(philosophers);
	free_struct(philosophers);
	return (0);
}
