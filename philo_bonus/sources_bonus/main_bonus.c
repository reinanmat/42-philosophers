/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:41:16 by revieira          #+#    #+#             */
/*   Updated: 2023/05/13 18:23:57 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	free_struct(t_philo *philo)
{
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	sem_close(philo->table->forks_in_table);
	free(philo->table);
	free(philo);
}

int	main(int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	return (0);
}
