/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:37:29 by revieira          #+#    #+#             */
/*   Updated: 2023/05/09 17:51:15 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitoring(void *arg)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time() - philo[i].last_meal > philo->data->time_to_die)
		{
			print_actions(&philo[i], DIED);
			exit(1);
		}
		i = (i + 1 + philo->data->nbr_of_philosophers) % philo->data->nbr_of_philosophers;
	}
}
