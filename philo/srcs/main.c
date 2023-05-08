/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:15:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/08 19:03:00 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static time_t	seconds_to_ms(time_t seconds)
{
	return (seconds * 1000);
}

static time_t	miliseconds_to_ms(time_t miliseconds)
{
	return (miliseconds / 1000);
}

time_t	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (seconds_to_ms(tv.tv_sec) + miliseconds_to_ms(tv.tv_usec));
}

time_t	get_time_stamp(time_t time_init)
{
	printf ("\n%ld\n", get_time() - time_init);
	return (get_time() - time_init);
}

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
	t_philo			*philo;
	pthread_mutex_t	*on_print;
	
	i = 0;
	num_philos = data->nbr_of_philosophers;
	philo = malloc(sizeof(t_philo) * num_philos);
	on_print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(on_print, NULL);
	while (i < num_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
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
	if (philo)
		free(philo);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->on_print);
	printf("Hello, philosophers num: %d\n", philo->id);
	pthread_mutex_unlock(philo->on_print);
	return (NULL);
}

void	create_threads(t_philo *philo)
{
	int	i;
	int	limit;

	i = 0;
	limit = philo->data->nbr_of_philosophers;
	while (i < limit)
	{
		pthread_create(&philo[i].th, NULL, &routine, (void *)&philo[i]);
		i++;
	}
	i = 0;
	while (i < limit)
	{
		pthread_join(philo[i].th, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philosophers;

	if (!check_args(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	philosophers = init_philosophers(&data);
	create_threads(philosophers);
	free_struct(philosophers);
}
