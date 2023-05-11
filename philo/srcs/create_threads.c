/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:45:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/11 17:27:52 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	monitoring(t_philo *philo, t_data *data)
{
	int		i;
	time_t	current_time;
	time_t	last_meal;

	while (1)
	{
		i = 0;
		while (i < data->nbr_of_philosophers)
		{
			current_time = get_time();	
			pthread_mutex_lock(philo[i].on_print);
			last_meal = philo[i].last_meal;
			pthread_mutex_unlock(philo[i].on_print);
			if (current_time - last_meal >= data->time_to_die)
			{
				pthread_mutex_lock(philo[i].mstop);
				philo[i].data->to_stop = 1;
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
	int		i;
	time_t	time;

	i = 0;
	time = get_time();
	while (i < data->nbr_of_philosophers)
	{
		philo[i].last_meal = time;
		pthread_create(&philo[i].th, NULL, &routine, (void *)&philo[i]);
		i++;
	}
	monitoring(philo, data);
}
