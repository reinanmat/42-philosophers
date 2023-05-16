/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:38:28 by revieira          #+#    #+#             */
/*   Updated: 2023/05/16 18:47:36 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

static void	exec_action(time_t time_to_action, t_philo *philo, char *action)
{
	time_t	current_time;
	time_t	death_time;
	time_t	time_to_exec_action;

	current_time = get_time();
	death_time = philo->last_meal + philo->data->time_to_die;
	time_to_exec_action = current_time + time_to_action;
	print_action(philo, action);
	if (time_to_exec_action > death_time)
	{
		usleep((death_time - current_time) * 1000);
		sem_wait(philo->on_print);
		printf("%ld	%d %s\n", get_timestamp(philo), philo->id, DIED);
		sem_post(philo->on_print);
		sem_post(philo->forks_in_table);
		sem_post(philo->forks_in_table);
		free_struct(philo);
		exit(1);
	}
	usleep(time_to_action * 1000);
}

static void	to_eat(t_philo *philo)
{
	sem_wait(philo->forks_in_table);
	sem_wait(philo->forks_in_table);
	print_action(philo, TAKEN_FORK);
	print_action(philo, TAKEN_FORK);
	exec_action(philo->data->time_to_eat, philo, EAT);
	philo->last_meal = get_time();
	philo->meals++;
	if (philo->meals == philo->data->meal_numbers)
	{
		sem_post(philo->forks_in_table);
		sem_post(philo->forks_in_table);
		free_struct(philo);
		exit(0);
	}
	sem_post(philo->forks_in_table);
	sem_post(philo->forks_in_table);
}

void	routine(t_philo *philo)
{
	philo->last_meal = get_time();
	if ((philo->id & 1) == 0)
		usleep(700);
	while (1)
	{
		to_eat(philo);
		exec_action(philo->data->time_to_sleep, philo, SLEEP); 
		print_action(philo, THINK);
		usleep(300);
	}
	exit(1);
}
