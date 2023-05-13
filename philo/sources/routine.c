/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:18:56 by revieira          #+#    #+#             */
/*   Updated: 2023/05/12 17:27:43 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	to_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->data->to_stop == 1 || philo->status == 0)
	{
		philo->status = 0;
		pthread_mutex_unlock(philo->mstop);
		return ;
	}
	pthread_mutex_unlock(philo->mstop);
	print_action(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	to_think(t_philo *philo)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->data->to_stop == 1 || philo->status == 0)
	{
		philo->status = 0;
		pthread_mutex_unlock(philo->mstop);
		return ;
	}
	pthread_mutex_unlock(philo->mstop);
	print_action(philo, THINK);
	usleep(500);
}

static void	exec_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->data->to_stop == 1)
	{
		philo->status = 0;
		pthread_mutex_unlock(philo->mstop);
		return ;
	}
	pthread_mutex_unlock(philo->mstop);
	if (!ft_strcmp(EAT, action))
	{
		print_action(philo, action);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(philo->mstop);
		philo->last_meal = get_time();
		philo->meals++;
		if (philo->meals == philo->data->meal_numbers)
			philo->status = 0;
		pthread_mutex_unlock(philo->mstop);
	}
	else
		print_action(philo, action);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id & 1) == 0)
		usleep(500);
	while (philo->status)
	{
		taken_fork(philo, 1);
		exec_action(philo, TAKEN_FORK);
		taken_fork(philo, 2);
		exec_action(philo, TAKEN_FORK);
		exec_action(philo, EAT);
		return_forks(philo);
		to_sleep(philo);
		to_think(philo);
	}
	return (NULL);
}
