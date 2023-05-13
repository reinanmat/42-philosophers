/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:14:15 by revieira          #+#    #+#             */
/*   Updated: 2023/05/04 17:43:27 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_pos_numbers(char *number)
{
	int	i;

	i = 0;
	while (ft_isspace(number[i]))
		i++;
	if (number[i] == '-')
	{
		printf("Error: negative number\n");
		return (0);
	}
	if (number[i] == '+')
		i++;
	while (ft_isdigit(number[i]))
		i++;
	while (ft_isspace(number[i]))
		i++;
	if (number[i] != '\0')
	{
		printf("Error: invalid number\n");
		return (0);
	}
	return (1);
}

static int	check_int_max(char *str)
{
	long long	number;
	size_t		digits;

	digits = ft_amount_of_digits(str);
	number = ft_atoill(str);
	if (digits > 10 || number > 2147483647)
	{
		printf("Error: invalid number bigger then INT_MAX\n");
		return (0);
	}
	return (1);
}

static int	check_numbers(char **argv, int (*funct)(char *))
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!funct(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	++argv;
	if (!check_numbers(argv, &check_pos_numbers))
		return (0);
	if (!check_numbers(argv, &check_int_max))
		return (0);
	if ((int)ft_atoill(argv[0]) < 1)
	{
		printf("Error: invalid numbers of philoshopers\n");
		return (0);
	}
	return (1);
}
