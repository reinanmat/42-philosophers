/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:52:47 by revieira          #+#    #+#             */
/*   Updated: 2023/05/17 14:56:39 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

static t_philo	*init_philos(int nbr_of_philos)
{
	int				i;
	sem_t			*on_print;
	sem_t			*forks;
	t_philo			*philo;

	philo = malloc(sizeof(t_philo) * nbr_of_philos);
	sem_unlink(PRINT);
	on_print = sem_open(PRINT, O_CREAT, 0777, 1);
	sem_unlink(FORKS);
	forks = sem_open(FORKS, O_CREAT, 0777, nbr_of_philos);
	i = -1;
	while (++i < nbr_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].on_print = on_print;
		philo[i].forks_in_table = forks;
	}
	return (philo);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->time_init = get_time();
	data->nbr_of_philos = (int)ft_atoill(argv[1]);
	data->time_to_die = (int)ft_atoill(argv[2]);
	data->time_to_eat = (int)ft_atoill(argv[3]);
	data->time_to_sleep = (int)ft_atoill(argv[4]);
	if (argc == 6)
		data->meal_numbers = (int)ft_atoill(argv[5]);
	else
		data->meal_numbers = -1;
	data->philos = init_philos(data->nbr_of_philos);
	return (data);
}
