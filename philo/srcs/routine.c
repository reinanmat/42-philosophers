/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:18:56 by revieira          #+#    #+#             */
/*   Updated: 2023/05/10 15:14:34 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	to_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->stop == 0)
	{
		return ;
		pthread_mutex_unlock(philo->mstop);
	}
	pthread_mutex_unlock(philo->mstop);
	pthread_mutex_lock(&philo->fork);
	print_action(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->fork_left);
	print_action(philo, TAKEN_FORK);
	print_action(philo, EAT);
	philo->last_meal = get_time();
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->fork_left);
}

static void	to_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->stop == 0)
	{
		return ;
		pthread_mutex_unlock(philo->mstop);
	}
	pthread_mutex_unlock(philo->mstop);
	print_action(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	to_think(t_philo *philo)
{
	pthread_mutex_lock(philo->mstop);
	if (philo->stop == 0)
	{
		return ;
		pthread_mutex_unlock(philo->mstop);
	}
	pthread_mutex_unlock(philo->mstop);
	print_action(philo, THINK);
	usleep(300);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if ((philo->id & 1) == 0)
		usleep(700);
	while (philo->stop)
	{
		to_eat(philo);
		to_sleep(philo);
		to_think(philo);
	}
	return (NULL);
}
