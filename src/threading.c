/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:29:56 by amakela           #+#    #+#             */
/*   Updated: 2024/06/30 18:09:25 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		philos[i++].last_meal = get_ms(philos);
	if (!create_threads(&supervisor, philos, philos->num_of_philos))
		join_threads(&supervisor, philos, philos->num_of_philos);
	pthread_mutex_destroy(philos->print);
	pthread_mutex_destroy(philos->eat);
	pthread_mutex_destroy(philos->kill);
	free_philos_and_forks(forks, philos, count);
	return (0);
}
