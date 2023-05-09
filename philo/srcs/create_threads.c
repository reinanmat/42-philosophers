/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:45:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/09 15:10:00 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_threads(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	th_monitoring;

	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		pthread_create(&philo[i].th, NULL, &routine, (void *)&philo[i]);
		i++;
	}
	pthread_create(&th_monitoring, NULL, &monitoring, (void *)philo);
	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		pthread_join(philo[i].th, NULL);
		i++;
	}
	pthread_join(th_monitoring, NULL);
}
