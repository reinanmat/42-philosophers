/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:15:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/12 17:17:29 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_struct(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->nbr_of_philosophers == 1)
	{
		pthread_mutex_destroy(philo[i].on_print);
		pthread_mutex_destroy(philo[i].mstop);
		free(philo[i].on_print);
		free(philo[i].mstop);
		free(philo);
		return ;
	}
	while (i < philo->data->nbr_of_philosophers)
	{
		pthread_join(philo[i].th, NULL);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(philo[i].on_print);
	pthread_mutex_destroy(philo[i].mstop);
	free(philo[i].on_print);
	free(philo[i].mstop);
	while (i < philo->data->nbr_of_philosophers)
	{
		pthread_mutex_destroy(&philo[i].fork);
		i++;
	}
	free(philo);
}

int	only_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, TAKEN_FORK);
	usleep(philo->data->time_to_die * 1000);
	print_action(philo, DIED);
	pthread_mutex_unlock(&philo->fork);
	free_struct(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philosophers;

	if (!check_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	philosophers = init_philosophers(&data);
	if (data.nbr_of_philosophers == 1)
		return (only_one_philo(philosophers));
	create_threads(philosophers, &data);
	free_struct(philosophers);
}
