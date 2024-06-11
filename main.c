/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:16:01 by amakela           #+#    #+#             */
/*   Updated: 2024/06/10 14:16:03 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		i ++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		prev = nbr;
		nbr = 10 * nbr + str[i++] - '0';
		if (prev > nbr)
			return (overflow(neg));
	}
	return ((int)nbr * neg);
}

int	check_values(t_data data) // useconds_t 0 - 1000000?
{
	if (data.philos < 1)
		return (-1);
	if (data.to_die < 1)
		return (-1);
	if (data.to_eat < 1)
		return (-1);
	if (data.to_sleep <1)
		return (-1);
	return (0);
}

void	init_data(int argc, char **argv, t_data *data)
{
	data->philos = ft_atoi(argv[1]);
	data->to_die = ft_atoi(argv[2]);
	data->to_eat = ft_atoi(argv[3]);
	data->to_sleep = ft_atoi(argv[4]);
	if (argv[argc - 1])
		data->meals = ft_atoi(argv[argc - 1]);
}

int	invalid_chars(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9') 
			{
				printf("error: arguments need to be digits only\n");
				return (-1);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	arg_validation(int argc, char **argv, t_data *data)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
	{
		printf("error: invalid amount of arguments\n");
		return (-1);
	}
	if (invalid_chars(argv))
		return (-1);
	init_data(argc, argv, data);
	if (check_values(*data) == -1)
	{
		printf("error: invalid value entered\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	if (arg_validation(argc, argv, &data) == -1)
		return (-1);
	return (0);
}
