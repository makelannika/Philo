/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:37:33 by amakela           #+#    #+#             */
/*   Updated: 2024/06/21 16:13:01 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status_change(char *message, t_philo *philo)
{
	if (!philo->dead)
	{
		pthread_mutex_lock(philo->print);
		printf("%d %d %s", get_ms(), philo->philo, message);
		pthread_mutex_unlock(philo->print);
	}
}

int	get_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	destroy_mutexes(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(philos[i++].fork_l);
}

int	free_philos_and_forks(pthread_mutex_t *forks, t_philo *philos, int count)
{
	destroy_mutexes(philos, count);
	free(forks);
	free(philos);
	return (1);
}

void	*kill_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
		philos[i++].dead = 1;
	return (NULL);
}
