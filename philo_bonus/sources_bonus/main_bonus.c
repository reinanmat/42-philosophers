/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:41:16 by revieira          #+#    #+#             */
/*   Updated: 2023/05/17 16:43:47 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	free_struct(t_data *data)
{
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	sem_close(data->philos->forks_in_table);
	sem_close(data->philos->on_print);
	free(data->philos);
	free(data);
}

int	only_one_philo(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		sem_post(data->philos->forks_in_table);
		print_action(data, data->philos, TAKEN_FORK);
		usleep(data->time_to_die * 1000);
		print_action(data, data->philos, DIED);
		sem_wait(data->philos->forks_in_table);
		free_struct(data);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	free_struct(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!check_args(argc, argv))
		return (1);
	data = init_data(argc, argv);
	if (data->nbr_of_philos == 1)
		return (only_one_philo(data));
	create_child_processes(data);
	free_struct(data);
	return (0);
}
