/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:43:58 by revieira          #+#    #+#             */
/*   Updated: 2023/05/12 14:32:10 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static time_t	seconds_to_ms(time_t seconds)
{
	return (seconds * 1000);
}

static time_t	microseconds_to_ms(time_t miliseconds)
{
	return (miliseconds / 1000);
}

time_t	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (seconds_to_ms(tv.tv_sec) + microseconds_to_ms(tv.tv_usec));
}

time_t	get_timestamp(t_philo *philo)
{
	return (get_time() - philo->data->time_init);
}
