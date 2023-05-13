/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:45:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/12 19:35:23 by revieira         ###   ########.fr       */
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

void	monitoring(t_philo *philo, t_data *data)
{
	int		i;
	int		status;

	while (1)
	{
		i = -1;
		usleep(500);
		while (++i < data->nbr_of_philos)
		{
			pthread_mutex_lock(philo[i].mstop);
			status = philo[i].status;
			if (status && get_time() - philo[i].last_meal > data->time_to_die)
			{
				philo[i].data->to_stop = 1;
				pthread_mutex_unlock(philo[i].mstop);
				print_action(&philo[i], DIED);
				return ;
			}
			pthread_mutex_unlock(philo[i].mstop);
		}
		if (get_remaining_philosophers(philo) == 0)
			break ;
	}
}
