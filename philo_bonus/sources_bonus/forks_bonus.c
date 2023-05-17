/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:08:34 by revieira          #+#    #+#             */
/*   Updated: 2023/05/17 12:10:10 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	taken_forks(t_philo *philo)
{
	sem_wait(philo->forks_in_table);
	sem_wait(philo->forks_in_table);
}

void	give_back_forks(t_philo *philo)
{
	sem_post(philo->forks_in_table);
	sem_post(philo->forks_in_table);
}
