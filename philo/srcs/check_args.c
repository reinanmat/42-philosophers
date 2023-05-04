/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: revieira <revieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:14:15 by revieira          #+#    #+#             */
/*   Updated: 2023/05/04 17:28:42 by revieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
