/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:38:28 by revieira          #+#    #+#             */
/*   Updated: 2023/05/15 17:22:34 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

static void	wait_for_time(time_t time, t_philo *philo)
{
	time_t init_time;

	init_time = get_time();
	while (get_time() - init_time <= time)
	{
		if (get_time() - philo->last_meal > philo->data->time_to_die)
		{
			print_action(philo, DIED);
			free_struct(philo);
			exit(1);
		}
		usleep(100);
	}
}

static void	to_eat(t_philo *philo)
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

static void	to_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	wait_for_time(philo->data->time_to_sleep, philo);
}

static void	to_think(t_philo *philo)
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

