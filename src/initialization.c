/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:31:23 by amakela           #+#    #+#             */
/*   Updated: 2024/07/06 22:08:00 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	set_mutex(t_mutex *mutexes, t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philos[i].fork_l = mutexes->forks + i;
		philos[i].print = &mutexes->print;
		if (i == count -1)
			philos[i].fork_r = mutexes->forks;
		else
			philos[i].fork_r = mutexes->forks + i + 1;
		i++;
	}
}

static int	init_eat_and_kill(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&philos[i].eat, NULL))
		{
			destroy_eat(philos, i);
			destroy_kill(philos, i);
			return (write(2, "error: pthread_mutex_init failed\n", 33));
		}
		if (pthread_mutex_init(&philos[i].kill, NULL))
		{
			destroy_kill(philos, i);
			destroy_eat(philos, i + 1);
			return (write(2, "error: pthread_mutex_init failed\n", 33));
		}
		i++;
	}
	return (0);
}

static int	init_forks(t_mutex *mutexes, t_philo *philos, int count)
{
	int	i;

	i = 0;
	mutexes->forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!mutexes->forks)
	{
		free(philos);
		return (write(2, "error: malloc failed\n", 21));
	}
	while (i < count)
	{
		if (pthread_mutex_init(mutexes->forks + i, NULL))
		{
			destroy_forks(mutexes->forks, i);
			free(philos);
			return (write(2, "error: pthread_mutex_init failed\n", 33));
		}
		i++;
	}
	return (0);
}

int	init_mutexes(t_mutex *mutexes, t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	count = philos->num_of_philos;
	if (init_forks(mutexes, philos, count))
		return (1);
	if (pthread_mutex_init(&mutexes->print, NULL))
	{
		destroy_forks(mutexes->forks, count);
		free(philos);
		return (write(2, "error: pthread_mutex_init failed\n", 33));
	}
	if (init_eat_and_kill(philos, count))
	{
		pthread_mutex_destroy(&mutexes->print);
		destroy_forks(mutexes->forks, count);
		free(philos);
		return (1);
	}
	set_mutex(mutexes, philos, count);
	return (0);
}

int	init_philos(t_philo **philos, int argc, char **argv)
{
	int				i;
	t_philo			philo;
	struct timeval	time;

	i = 0;
	philo = (t_philo){0};
	*philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!*philos)
		return (write(2, "error: malloc failed\n", 21));
	philo.num_of_philos = ft_atoi(argv[1]);
	philo.to_die = ft_atoi(argv[2]);
	philo.to_eat = ft_atoi(argv[3]);
	philo.to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.meals = ft_atoi(argv[5]);
	else
		philo.meals = -1;
	gettimeofday(&time, NULL);
	philo.beginning = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (i < philo.num_of_philos)
	{
		philo.philo = i + 1;
		(*philos)[i++] = philo;
	}
	return (0);
}
