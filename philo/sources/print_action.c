/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:53:01 by revieira          #+#    #+#             */
/*   Updated: 2023/05/10 12:46:57 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_action(t_philo *philo, char *action)
{
	time_t	timestamp;

	pthread_mutex_lock(philo->on_print);
	timestamp = get_timestamp(philo);
	printf("%ld	%d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(philo->on_print);
}
