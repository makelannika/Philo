/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:11:36 by amakela           #+#    #+#             */
/*   Updated: 2024/06/12 17:16:37 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

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
	gettimeofday(&data->beginning, NULL);
}

int	invalid_chars(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
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

void	*func()
{
	printf("hello\n");
	return (NULL);
}

int	get_philos(int count)
{
	int			i;
	pthread_t	philos[count];

	i = 0;
	while (i < count)
	{
		if (pthread_create(&philos[i], NULL, &func, NULL) != 0)
		{
			printf("error: creating threads failed\n");
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (pthread_join(philos[i], NULL) != 0)
		{
			printf("joining threads failed\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	data = (t_data){0};
	if (arg_validation(argc, argv, &data) == -1)
		return (-1);
	// printf("BEGINNING\nsec: %ld\nusec: %ld\n", data.beginning.tv_sec, data.beginning.tv_usec);
	if (get_philos(data.philos) == -1)
		return (-1);
	return (0);
}
