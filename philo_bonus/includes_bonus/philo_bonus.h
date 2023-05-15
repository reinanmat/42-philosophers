/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:13 by revieira          #+#    #+#             */
/*   Updated: 2023/05/15 16:59:15 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define TAKEN_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

# define FORKS "/forks"
# define PRINT "/print"

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_data
{
	time_t	time_init;
	int		nbr_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meal_numbers;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				status;
	int				meals;
	time_t			last_meal;
	sem_t			*forks_in_table;
	sem_t			*on_print;
	t_data			*data;
}	t_philo;

//check_args_bonus
int			check_args(int argc, char **argv);

//init_struct
void		init_data(int argc, char **argv, t_data *data);
t_philo		*init_philosophers(t_data *data);

void		free_struct(t_philo *philo);

void		create_child_processes(t_philo *philo);

//get_time
time_t		get_time(void);
time_t		get_timestamp(t_philo *philo);

//utils_Bonus
int			ft_isdigit(char c);
int			ft_isspace(char c);
size_t		ft_amount_of_digits(char *str);
long long	ft_atoill(char *str);
int			ft_strcmp(const char *s1, const char *s2);

#endif
