/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:29:56 by amakela           #+#    #+#             */
/*   Updated: 2024/06/19 21:32:05 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*supervise(void *ptr)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)ptr;
	while (1)
	{
		if (i == philos->num_of_philos)
			i = 0;
		if (!philos[i].meals)
			return (NULL);
		pthread_mutex_lock(philos->eat);
		if (get_ms() > philos[i].last_meal + philos[i].to_die)
		{
			pthread_mutex_lock(philos->print);
			printf("%d Philo %d died\n", get_ms(), philos[i].philo);
			pthread_mutex_unlock(philos->print);
			kill_philos(philos, philos->num_of_philos);
			return (NULL);
		}
		pthread_mutex_unlock(philos->eat);
		i++;
	}
}

static int	join_threads(pthread_t *supervisor, t_philo *philos, int count)
{
	int	i;

	i = 0;
	if (pthread_join(*supervisor, NULL))
		return (write(2, "joining threads failed\n", 23));
	while (i < count)
	{
		if (pthread_join(philos[i++].thread, NULL))
			return (write(2, "joining threads failed\n", 23));
	}
	return (0);
}

static int	create_threads(pthread_t *supervisor, t_philo *philos, int count)
{
	int	i;

	i = 0;
	if (pthread_create(supervisor, NULL, &supervise, philos))
		return (write(2, "creating threads failed\n", 24));
	while (i < count)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
			return (write(2, "creating threads failed\n", 24));
		i++;
	}
	return (0);
}

int	threading(pthread_mutex_t *forks, t_philo *philos, int count)
{
	int			i;
	pthread_t	supervisor;

	i = 0;
	while (i < philos->num_of_philos)
		philos[i++].last_meal = get_ms();
	if (!create_threads(&supervisor, philos, philos->num_of_philos))
		join_threads(&supervisor, philos, philos->num_of_philos);
	pthread_mutex_destroy(philos->print);
	pthread_mutex_destroy(philos->eat);
	free_all(forks, philos, count);
	return (0);
}
