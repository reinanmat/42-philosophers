/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:15:02 by revieira          #+#    #+#             */
/*   Updated: 2023/05/04 17:15:59 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(char **argv, t_data *data)
{
	data = malloc(sizeof(t_data));
	data->numbers_of_philosophers = (int)ft_atoill(argv[0]);
	data->time_to_die = (int)ft_atoill(argv[1]);
	data->time_to_eat = (int)ft_atoill(argv[2]);
	data->time_to_sleep = (int)ft_atoill(argv[3]);
	data->number_of_time_each_philosopher_must_eat = (int)ft_atoill(argv[4]);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (!check_args(argc, argv))
		return (1);
	init_data(argv, data);
}
