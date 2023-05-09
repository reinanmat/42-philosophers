/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:53:01 by revieira          #+#    #+#             */
/*   Updated: 2023/05/09 16:23:03 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_actions(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->on_print);
	printf("%ld	%d %s\n", get_time_stamp(philo), philo->id, action);
	pthread_mutex_unlock(philo->on_print);
}
