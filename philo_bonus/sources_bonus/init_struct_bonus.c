/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:52:47 by revieira          #+#    #+#             */
/*   Updated: 2023/05/13 18:03:20 by revieira         ###   ########.fr       */
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

t_table	*init_table(int nbr_of_philos)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	sem_unlink(FORKS);
	table->forks_in_table = sem_open(FORKS, O_CREAT, 0777, nbr_of_philos);
	return (table);
}

t_philo	*init_philosophers(t_data *data)
{
	int				i;
	sem_t			*on_print;
	t_philo			*philo;
	t_table			*table;

	table = init_table(data->nbr_of_philos);
	philo = malloc(sizeof(t_philo) * data->nbr_of_philos);
	sem_unlink(PRINT);
	on_print = sem_open(PRINT, O_CREAT, 0777, 1);
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].status = 1;
		philo[i].on_print = on_print;
		philo[i].fork_left = table->forks_in_table;
		philo[i].fork_right = table->forks_in_table;
		philo[i].data = data;
		philo[i].table = table;
	}
	return (philo);
}
