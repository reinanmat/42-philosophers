/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:41:16 by revieira          #+#    #+#             */
/*   Updated: 2023/05/15 15:57:20 by revieira         ###   ########.fr       */
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

void	to_eat(t_philo *philo)
{
	sem_wait(philo->forks_in_table);
	print_action(philo, TAKEN_FORK);
	sem_wait(philo->forks_in_table);
	print_action(philo, TAKEN_FORK);
	print_action(philo, EAT);
	usleep(philo->data->time_to_eat * 1000);
	philo->last_meal = get_time();
	sem_post(philo->forks_in_table);
	sem_post(philo->forks_in_table);
	philo->meals++;
	if (philo->meals == philo->data->meal_numbers)
	{
		free_struct(philo);
		exit(1);
	}
}

void	to_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	wait_for_time(philo->data->time_to_sleep, philo);
}

void	to_think(t_philo *philo)
{
	print_action(philo, THINK);
	usleep(500);
	while (*(int *)philo->forks_in_table < 1)
		wait_for_time(1000, philo);
}

void	routine(t_philo *philo)
{
	philo->last_meal = get_time();
	if ((philo->id & 1) == 0)
		wait_for_time(philo->data->time_to_eat / 2, philo);
	while (philo->status)
	{
		to_eat(philo);
		to_sleep(philo);
		to_think(philo);
	}
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
