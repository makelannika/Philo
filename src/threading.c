/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:29:56 by amakela           #+#    #+#             */
/*   Updated: 2024/07/08 22:05:08 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	join_threads(pthread_t *supervisor, t_philo *philos, int count)
{
	int	i;

	i = 0;
	if (pthread_join(*supervisor, NULL))
		return (write(2, "error: pthread_join failed\n", 27));
	while (i < count)
	{
		if (pthread_join(philos[i++].thread, NULL))
			return (write(2, "error: pthread_join failed\n", 27));
	}
	return (0);
}

static int	create_threads(pthread_t *supervisor, t_philo *philos, int count)
{
	int	i;

	i = 0;
	if (pthread_create(supervisor, NULL, &supervise, philos))
		return (write(2, "error: pthread_create failed\n", 29));
	while (i < count)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]))
		{
			kill_philos(philos, i);
			join_threads(supervisor, philos, i);
			return (write(2, "error: pthread_create failed\n", 29));
		}
		i++;
	}
	return (0);
}

int	threading(t_mutex *mutexes, t_philo *philos)
{
	int			ret;
	pthread_t	supervisor;

	ret = 0;
	if (!create_threads(&supervisor, philos, philos->num_of_philos))
		ret = join_threads(&supervisor, philos, philos->num_of_philos);
	else
		ret++;
	free_and_destroy(*mutexes, philos);
	return (ret);
}
