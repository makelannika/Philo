/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:10:42 by amakela           #+#    #+#             */
/*   Updated: 2024/06/30 18:59:40 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*kill_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philos->kill);
	while (i < count)
		philos[i++].dead = 1;
	pthread_mutex_unlock(philos->kill);
	return (NULL);
}

static int	all_ate(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philos->eat);
	while (i < philos->num_of_philos)
	{
		if (philos[i].meals != 0)
		{
			pthread_mutex_unlock(philos->eat);
			return (0);
		}
		i++;
	}
	pthread_mutex_lock(philos->print);
	kill_philos(philos, philos->num_of_philos);
	pthread_mutex_unlock(philos->print);
	pthread_mutex_unlock(philos->eat);
	return (1);
}

void	*supervise(void *ptr)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)ptr;
	while (1)
	{
		if (i == philos->num_of_philos)
			i = 0;
		if (all_ate(philos))
			return (NULL);
		pthread_mutex_lock(philos->eat);
		if (get_ms(philos) > philos[i].last_meal + philos[i].to_die)
		{
			pthread_mutex_lock(philos->print);
			printf("%d %d died\n", get_ms(philos), philos[i].philo);
			kill_philos(philos, philos->num_of_philos);
			pthread_mutex_unlock(philos->print);
			pthread_mutex_unlock(philos->eat);
			return (NULL);
		}
		pthread_mutex_unlock(philos->eat);
		i++;
	}
}
