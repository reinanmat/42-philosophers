/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:45:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/10 14:57:06 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	monitoring(t_philo *philo, t_data *data)
{
	int		i;
	time_t	current_time;

	while (1)
	{
		i = 0;
		while (i < data->nbr_of_philosophers)
		{
			current_time = get_time();	
			if (current_time - philo[i].last_meal >= data->time_to_die)
			{
				pthread_mutex_lock(philo[i].mstop);
				philo[i].stop[0] = 0;
				pthread_mutex_unlock(philo[i].mstop);
				print_action(&philo[i], DIED);
				return (1);
			}
			i++;
		}
	}
}

void	create_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		philo[i].last_meal = get_time();
		pthread_create(&philo[i].th, NULL, &routine, (void *)&philo[i]);
		i++;
	}
	monitoring(philo, data);
}
