/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:31:23 by amakela           #+#    #+#             */
/*   Updated: 2024/06/30 17:59:51 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	set_mutex(t_mutex *mutexes, t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->num_of_philos == 1)
	{
		philos[i].fork_l = mutexes->forks + i;
		philos[i].print = &mutexes->print;
		philos[i].eat = &mutexes->eat;
		philos[i].kill = &mutexes->kill;
		return ;
	}
	while (i < philos->num_of_philos)
	{
		philos[i].fork_l = mutexes->forks + i;
		philos[i].print = &mutexes->print;
		philos[i].eat = &mutexes->eat;
		philos[i].kill = &mutexes->kill;
		if (i == philos->num_of_philos -1)
			philos[i].fork_r = mutexes->forks;
		else
			philos[i].fork_r = mutexes->forks + i + 1;
		i++;
	}
}

static int	init_forks(t_mutex *mutexes, t_philo *philos)
{
	int	i;

	i = 0;
	mutexes->forks = malloc(sizeof(pthread_mutex_t) * philos->num_of_philos);
	if (!mutexes->forks)
	{
		free(philos);
		return (1);
	}
	while (i < philos->num_of_philos)
	{
		if (pthread_mutex_init(mutexes->forks + i, NULL))
			return (free_philos_and_forks(mutexes->forks, philos, i));
		i++;
	}
	return (0);
}

int	init_mutexes(t_mutex *mutexes, t_philo *philos)
{
	int	count;

	count = philos->num_of_philos;
	if (init_forks(mutexes, philos))
		return (1);
	if (pthread_mutex_init(&mutexes->print, NULL))
		return (free_philos_and_forks(mutexes->forks, philos, count));
	if (pthread_mutex_init(&mutexes->eat, NULL))
	{
		pthread_mutex_destroy(&mutexes->print);
		return (free_philos_and_forks(mutexes->forks, philos, count));
	}
	if (pthread_mutex_init(&mutexes->kill, NULL))
	{
		pthread_mutex_destroy(&mutexes->print);
		pthread_mutex_destroy(&mutexes->eat);
		return (free_philos_and_forks(mutexes->forks, philos, count));
	}
	set_mutex(mutexes, philos);
	return (0);
}

int	init_philos(t_philo **philos, int argc, char **argv)
{
	int				i;
	t_philo			philo;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	*philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!*philos)
		return (write(2, "error: malloc failed\n", 21));
	philo = (t_philo){0};
	philo.num_of_philos = ft_atoi(argv[1]);
	philo.dead = 0;
	philo.to_die = ft_atoi(argv[2]);
	philo.to_eat = ft_atoi(argv[3]);
	philo.to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.meals = ft_atoi(argv[5]);
	else
		philo.meals = -1;
	philo.beginning = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (i < philo.num_of_philos)
	{
		philo.philo = i + 1;
		(*philos)[i++] = philo;
	}
	return (0);
}
