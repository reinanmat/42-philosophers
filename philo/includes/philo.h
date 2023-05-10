/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:30:00 by revieira          #+#    #+#             */
/*   Updated: 2023/05/10 13:04:43 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKEN_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_data
{
	time_t	time_init;
	int		nbr_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meal_numbers;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				*stop;
	time_t			last_meal;
	pthread_t		th;
	pthread_mutex_t	fork;
	pthread_mutex_t *fork_left;
	pthread_mutex_t	*on_print;
	pthread_mutex_t	*mstop;
	t_data			*data;
}	t_philo;

int			check_args(int argc, char **argv);

//Create_threads
void		create_threads(t_philo *philo, t_data *info);

//Print Actions
void		print_actions(t_philo *philo, char *action);

//Threads
void		*routine(void *arg);

//Get_time
time_t		get_time(void);
time_t		get_time_stamp(t_philo *philo);

// Utils
int			ft_isdigit(char c);
int			ft_isspace(char c);
size_t		ft_amount_of_digits(char *str);
long long	ft_atoill(char *str);

#endif
