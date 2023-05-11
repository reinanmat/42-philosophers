/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:18:56 by revieira          #+#    #+#             */
/*   Updated: 2023/05/11 16:54:33 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	to_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->data->to_stop == 1)
	{
		pthread_mutex_unlock(philo->mstop);
		return (0);
	}
	pthread_mutex_unlock(philo->mstop);
	print_action(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	return (1);
}

static int	to_think(t_philo *philo)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->data->to_stop == 1)
	{
		pthread_mutex_unlock(philo->mstop);
		return (0);
	}
	pthread_mutex_unlock(philo->mstop);
	print_action(philo, THINK);
	usleep(500);
	return (1);
}

static int	exec_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->data->to_stop == 1)
	{
		pthread_mutex_unlock(philo->mstop);
		return (0);
	}
	pthread_mutex_unlock(philo->mstop);
	if (!ft_strcmp(EAT, action))
	{
		print_action(philo, action);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_lock(philo->on_print);
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->on_print);
		philo->meals++;
	}
	else
		print_action(philo, action);
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if ((philo->id & 1) == 0)
		usleep(500);
	while (philo->status)
	{
		pthread_mutex_lock(&philo->fork);
		philo->status = exec_action(philo, TAKEN_FORK);
		pthread_mutex_lock(philo->fork_left);
		philo->status = exec_action(philo, TAKEN_FORK);
		philo->status = exec_action(philo, EAT);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->fork_left);
		philo->status = to_sleep(philo);
		philo->status = to_think(philo);
	}
	return (NULL);
}
