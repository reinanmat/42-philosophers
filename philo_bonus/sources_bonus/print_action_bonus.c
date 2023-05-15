/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:36:43 by revieira          #+#    #+#             */
/*   Updated: 2023/05/15 16:37:20 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/philo_bonus.h"

void	print_action(t_philo *philo, char *action)
{
	sem_wait(philo->on_print);
	printf("%ld	%d %s\n", get_timestamp(philo), philo->id, action);
	sem_post(philo->on_print);
}
