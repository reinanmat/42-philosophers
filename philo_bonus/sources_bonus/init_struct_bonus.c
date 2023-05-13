/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:52:47 by revieira          #+#    #+#             */
/*   Updated: 2023/05/13 13:07:16 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	init_data(int argc, char **argv, t_data *data)
{
	data->time_init = get_time();
	data->nbr_of_philos = (int)ft_atoill(argv[1]);
	data->time_to_die = (int)ft_atoill(argv[2]);
	data->time_to_eat = (int)ft_atoill(argv[3]);
	data->time_to_sleep = (int)ft_atoill(argv[4]);
	if (argc == 6)
		data->meal_numbers = (int)ft_atoill(argv[5]);
	else
		data->meal_numbers = -1;
}

t_philo	*init_philosophers(t_data *data)
{
	int				i;
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].meals = 0;
		philo[i].status = 1;
	}
	return (philo);
}
