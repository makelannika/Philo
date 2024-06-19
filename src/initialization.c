/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:31:23 by amakela           #+#    #+#             */
/*   Updated: 2024/06/19 20:58:54 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_mutex(pthread_mutex_t *forks, pthread_mutex_t *eat,
		pthread_mutex_t *print, t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->num_of_philos == 1)
	{
		philos[i].fork_l = &forks[i];
		philos[i].print = print;
		philos[i].eat = eat;
		return ;
	}
	while (i < philos->num_of_philos)
	{
		philos[i].fork_l = &forks[i];
		philos[i].fork_r = &forks[i + 1];
		philos[i].print = print;
		philos[i].eat = eat;
		i++;
	}
	philos[i - 1].fork_r = &forks[0];
}

int	init_mutexes(pthread_mutex_t **forks, pthread_mutex_t *eat,
		pthread_mutex_t *print, t_philo *philos)
{
	int	i;

	i = 0;
	*forks = malloc(sizeof(pthread_mutex_t) * philos->num_of_philos);
	if (!*forks)
	{
		free(philos);
		return (1);
	}
	while (i < philos->num_of_philos)
	{
		if (pthread_mutex_init(*forks + i, NULL))
			return (free_all(*forks, philos, i));
		i++;
	}
	if (pthread_mutex_init(print, NULL))
		return (free_all(*forks, philos, i));
	if (pthread_mutex_init(eat, NULL))
	{
		pthread_mutex_destroy(print);
		return (free_all(*forks, philos, i));
	}
	set_mutex(*forks, eat, print, philos);
	return (0);
}

int	init_philos(t_philo **philos, int argc, char **argv)
{
	int		i;
	t_philo	philo;

	i = 0;
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
	while (i < philo.num_of_philos)
	{
		philo.philo = i + 1;
		(*philos)[i++] = philo;
	}
	return (0);
}
