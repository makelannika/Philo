/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:27:32 by amakela           #+#    #+#             */
/*   Updated: 2024/07/09 19:38:04 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;
	int		sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = 10 * nbr + str[i++] - '0';
		if (nbr > INT_MAX)
			return (-1);
	}
	return ((int)nbr * sign);
}

static int	check_values(char **argv)
{
	if (ft_atoi(argv[1]) < 1)
		return (write(2, "error: invalid number of philosophers\n", 38));
	if (ft_atoi(argv[2]) < 1)
		return (write(2, "error: invalid time to die\n", 27));
	if (ft_atoi(argv[3]) < 1)
		return (write(2, "error: invalid time to eat\n", 27));
	if (ft_atoi(argv[4]) < 1)
		return (write(2, "error: invalid time to sleep\n", 29));
	if (argv[5] && ft_atoi(argv[5]) < 1)
		return (write(2, "error: invalid number of meals\n", 31));
	return (0);
}

int	arg_validation(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write(2, "error: invalid amount of arguments\n", 35));
	return (check_values(argv));
}
