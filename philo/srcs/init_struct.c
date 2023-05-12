/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:52:47 by revieira          #+#    #+#             */
/*   Updated: 2023/05/12 17:29:02 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(int argc, char **argv, t_data *data)
{
	data->time_init = get_time();
	data->nbr_of_philos = (int)ft_atoill(argv[1]);
	data->time_to_die = (int)ft_atoill(argv[2]);
	data->time_to_eat = (int)ft_atoill(argv[3]);
	data->time_to_sleep = (int)ft_atoill(argv[4]);
	data->to_stop = 0;
	if (argc == 6)
		data->meal_numbers = (int)ft_atoill(argv[5]);
	else
		data->meal_numbers = -1;
}

static int	next_philo(int current_philo, int num_philos)
{
	return ((current_philo + 1 + num_philos) % num_philos);
}

t_philo	*init_philosophers(t_data *data)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*on_print;
	pthread_mutex_t	*mstop;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->nbr_of_philos);
	mstop = malloc(sizeof(pthread_mutex_t));
	on_print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mstop, NULL);
	pthread_mutex_init(on_print, NULL);
	while (++i < data->nbr_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].meals = 0;
		philo[i].status = 1;
		philo[i].mstop = mstop;
		philo[i].on_print = on_print;
		pthread_mutex_init(&philo[i].fork, NULL);
	}
	i = -1;
	while (++i < data->nbr_of_philos)
		philo[i].fork_left = &philo[next_philo(i, data->nbr_of_philos)].fork;
	return (philo);
}
