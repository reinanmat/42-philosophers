/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:38:28 by revieira          #+#    #+#             */
/*   Updated: 2023/05/17 14:29:06 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

static void	exec_action(time_t time_to_action, t_data *data, t_philo *philo)
{
	time_t	current_time;
	time_t	death_time;
	time_t	time_to_exec_action;

	current_time = get_time();
	death_time = philo->last_meal + data->time_to_die;
	time_to_exec_action = current_time + time_to_action;
	if (time_to_exec_action > death_time)
	{
		usleep((death_time - current_time) * 1000);
		sem_wait(philo->on_print);
		printf("%ld	%d died\n", get_timestamp(data->time_init), philo->id);
		free_struct(data);
		exit(1);
	}
	usleep(time_to_action * 1000);
}

static void	to_eat(t_data *data, t_philo *philo)
{
	sem_wait(philo->forks_in_table);
	sem_wait(philo->forks_in_table);
	print_action(data, philo, TAKEN_FORK);
	print_action(data, philo, TAKEN_FORK);
	print_action(data, philo, EAT);
	exec_action(data->time_to_eat, data, philo);
	philo->last_meal = get_time();
	philo->meals++;
	if (philo->meals == data->meal_numbers)
	{
		sem_post(philo->forks_in_table);
		sem_post(philo->forks_in_table);
		free_struct(data);
		exit(0);
	}
	sem_post(philo->forks_in_table);
	sem_post(philo->forks_in_table);
}

static void	to_sleep(t_data *data, t_philo *philo)
{
	print_action(data, philo, SLEEP);
	exec_action(data->time_to_sleep, data, philo); 
}

static void to_think(t_data *data, t_philo *philo)
{
	print_action(data, philo, THINK);
	usleep(500);
}

void	routine(t_data *data, t_philo *philo)
{
	philo->last_meal = get_time();
	if ((philo->id & 1) == 0)
		usleep(500);
	while (1)
	{
		to_eat(data, philo);
		to_sleep(data, philo);
		to_think(data, philo);
	}
	exit(1);
}
