/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:45:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/12 17:30:32 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	get_remaining_philosophers(t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo->data->nbr_of_philos)
	{
		pthread_mutex_lock(philo[i].mstop);
		status = philo[i].status;
		pthread_mutex_unlock(philo[i].mstop);
		if (status)
			return (1);
		i++;
	}
	return (0);
}

int	monitoring(t_philo *philo, t_data *data)
{
	int		i;
	int		status;
	time_t	current_time;
	time_t	last_meal;

	while (1)
	{
		i = 0;
		usleep(500);
		while (i < data->nbr_of_philos)
		{
			current_time = get_time();
			pthread_mutex_lock(philo[i].mstop);
			last_meal = philo[i].last_meal;
			status = philo[i].status;
			pthread_mutex_unlock(philo[i].mstop);
			if (status && current_time - last_meal > data->time_to_die)
			{
				pthread_mutex_lock(philo[i].mstop);
				philo[i].data->to_stop = 1;
				pthread_mutex_unlock(philo[i].mstop);
				print_action(&philo[i], DIED);
				return (1);
			}
			i++;
		}
		if (get_remaining_philosophers(philo) == 0)
			break ;
	}
	return (0);
}
