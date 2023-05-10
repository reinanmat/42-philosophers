/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:15:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/10 13:04:32 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(int argc, char **argv, t_data *data)
{
	data->time_init = get_time();
	data->nbr_of_philosophers = (int)ft_atoill(argv[1]);
	data->time_to_die = (int)ft_atoill(argv[2]);
	data->time_to_eat = (int)ft_atoill(argv[3]);
	data->time_to_sleep = (int)ft_atoill(argv[4]);
	if (argc == 6)
		data->meal_numbers = (int)ft_atoill(argv[5]);
	else
		data->meal_numbers = -1;
}

/* t_philo	*init_philosophers(t_data *data) */
/* { */
/* 	int				i; */
/* 	int				num_philos; */
/* 	t_philo			*philo; */
	
/* 	i = 0; */
/* 	num_philos = data->nbr_of_philosophers; */
/* 	philo = malloc(sizeof(t_philo) * num_philos); */
/* 	philo[0].on_print = malloc(sizeof(pthread_mutex_t)); */
/* 	pthread_mutex_init(philo[0].on_print, NULL); */
/* 	while (i < num_philos) */
/* 	{ */
/* 		philo[i].id = i + 1; */
/* 		philo[i].data = data; */
/* 		pthread_mutex_init(&philo[i].fork, NULL); */
/* 		i++; */
/* 	} */
/* 	i = 0; */
/* 	while (i < num_philos) */
/* 	{ */
/* 		 philo[i].fork_left = &philo[(i + 1 + num_philos) % num_philos].fork; */
/* 		 philo[i].on_print = philo[0].on_print; */
/* 		 i++; */
/* 	} */
/* 	return (philo); */
/* } */

t_philo	*init_philosophers(t_data *data)
{
	int				i;
	int				num_philos;
	int				*stop_value;
	t_philo			*philo;
	pthread_mutex_t	*on_print;
	pthread_mutex_t	*mstop;
	
	i = 0;
	num_philos = data->nbr_of_philosophers;
	philo = malloc(sizeof(t_philo) * num_philos);
	mstop = malloc(sizeof(pthread_mutex_t));
	on_print = malloc(sizeof(pthread_mutex_t));
	stop_value = malloc(sizeof(int));
	*stop_value = 1;
	pthread_mutex_init(mstop, NULL);
	pthread_mutex_init(on_print, NULL);
	while (i < num_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].stop = stop_value;
		philo[i].mstop = mstop;
		philo[i].on_print = on_print;
		pthread_mutex_init(&philo[i].fork, NULL);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		 philo[i].fork_left = &philo[(i + 1 + num_philos) % num_philos].fork;
		 i++;
	}
	return (philo);
}

void	free_struct(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo[i].on_print);
	free(philo[i].on_print);
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
	print_actions(philo, TAKEN_FORK);
	usleep(philo->data->time_to_die * 1000);
	print_actions(philo, DIED);
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
