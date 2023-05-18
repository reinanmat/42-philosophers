/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:42:13 by revieira          #+#    #+#             */
/*   Updated: 2023/05/18 15:10:46 by revieira         ###   ########.fr       */
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
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int		id;
	int		meals;
	time_t	last_meal;
	sem_t	*forks_in_table;
	sem_t	*on_print;
	sem_t	*on_exec;
}	t_philo;

typedef struct s_data
{
	int		nbr_of_philos;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	meal_numbers;
	time_t	time_init;
	t_philo	*philos;
}	t_data;

//check_args_bonus
int			check_args(int argc, char **argv);

//init_struct
t_data		*init_data(int argc, char **argv);

//main
void		free_struct(t_data *data);

//Child_processes
void		create_child_processes(t_data *data);

//get_time
time_t		get_time(void);
time_t		get_timestamp(time_t time_init);

//Forks
void		taken_forks(t_philo *philo);
void		give_back_forks(t_philo *philo);

//Routine
void		routine(t_data *data, t_philo *philo);

//print_action
void		print_action(t_data *data, t_philo *philo, char *action);

//utils_Bonus
int			ft_isdigit(char c);
int			ft_isspace(char c);
size_t		ft_amount_of_digits(char *str);
long long	ft_atoill(char *str);
int			ft_strcmp(const char *s1, const char *s2);

#endif
