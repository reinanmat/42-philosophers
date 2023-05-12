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

void	free_struct(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos && data->nbr_of_philos != 1)
	{
		pthread_join(philo[i].th, NULL);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(philo[i].on_print);
	pthread_mutex_destroy(philo[i].mstop);
	free(philo[i].on_print);
	free(philo[i].mstop);
	if (philo->data->nbr_of_philos == 1)
	{
		free(philo);
		return ;
	}
	while (i < data->nbr_of_philos && data->nbr_of_philos != 1)
	{
		pthread_mutex_destroy(&philo[i].fork);
		i++;
	}
	free(philo);
}

void	create_threads(t_philo *philo, t_data *data)
{
	int		i;
	time_t	time;

	i = 0;
	time = get_time();
	while (i < data->nbr_of_philos)
	{
		philo[i].last_meal = time;
		pthread_create(&philo[i].th, NULL, &routine, (void *)&philo[i]);
		i++;
	}
}

int	only_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, TAKEN_FORK);
	usleep(philo->data->time_to_die * 1000);
	print_action(philo, DIED);
	pthread_mutex_unlock(&philo->fork);
	free_struct(philo->data, philo);
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
