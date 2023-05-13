/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:08:19 by revieira          #+#    #+#             */
/*   Updated: 2023/05/12 17:08:46 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	taken_fork(t_philo *philo, int fork_num)
{
	if (fork_num == 1)
	{
		if ((philo->id & 1) == 0)
			pthread_mutex_lock(&philo->fork);
		else
			pthread_mutex_lock(philo->fork_left);
	}
	else
	{
		if ((philo->id & 1) == 0)
			pthread_mutex_lock(philo->fork_left);
		else
			pthread_mutex_lock(&philo->fork);
	}
}

void	return_forks(t_philo *philo)
{
	if ((philo->id & 1) == 0)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->fork_left);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(&philo->fork);
	}
}
