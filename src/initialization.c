/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:31:23 by amakela           #+#    #+#             */
/*   Updated: 2024/06/18 19:57:32 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_mutex(pthread_mutex_t *fork, pthread_mutex_t *print, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].fork_l = &fork[i];
		philo[i].fork_r = &fork[i + 1];
		philo[i].print = print;
		i++;
	}
	philo[i - 1].fork_r = &fork[0];
}

int	init_mutexes(pthread_mutex_t *forks, pthread_mutex_t *print, t_philo *philo)
{
	int	i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philos);
	if (!forks)
	{
		free(philo);
		return (1);
	}
	while (i < philo->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
			return (free_all(forks, philo, i));
	}
	if (pthread_mutex_init(print, NULL))
		return (free_all(forks, philo, i));
	set_mutex(forks, print, philo);
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
