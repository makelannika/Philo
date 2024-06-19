/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:27:32 by amakela           #+#    #+#             */
/*   Updated: 2024/06/19 17:26:27 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	overflow(int neg)
{
	if (neg == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;
	int		neg;
	long	prev;

	i = 0;
	nbr = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i ++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = nbr;
		nbr = 10 * nbr + str[i++] - '0';
		if (prev > nbr)
			return (overflow(neg));
	}
	return ((int)nbr * neg);
}

static int	check_values(char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (write(2, "error: invalid number of philosophers\n", 31));
	if (ft_atoi(argv[2]) < 1)
		return (write(2, "error: invalid time to die\n", 20));
	if (ft_atoi(argv[3]) < 1)
		return (write(2, "error: invalid time to eat\n", 20));
	if (ft_atoi(argv[4]) < 1)
		return (write(2, "error: invalid time to sleep\n", 22));
	if (argv[5] && ft_atoi(argv[5]) < 1)
		return (write(2, "error: invalid number of meals\n", 24));
	return (0);
}

int	arg_validation(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
		return (write(2, "invalid amount of arguments\n", 28));
	while (argv[i])
	{
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (write(2, "arguments need to be numbers only\n", 34));
			j++;
		}
		i++;
		j = 0;
	}
	return (check_values(argv));
}
