/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:37:33 by amakela           #+#    #+#             */
/*   Updated: 2024/06/30 19:10:54 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	do_sleep(int time, t_philo *philo)
{
	pthread_mutex_lock(philo->kill);
	if (!philo->dead)
	{
		pthread_mutex_unlock(philo->kill);
		usleep(time * 1000);
		return ;
	}
	pthread_mutex_unlock(philo->kill);
}

void	print_status_change(char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->kill);
	if (!philo->dead)
	{
		pthread_mutex_unlock(philo->kill);
		pthread_mutex_lock(philo->print);
		printf("%d %d %s", get_ms(philo), philo->philo, message);
		pthread_mutex_unlock(philo->print);
		return ;
	}
	pthread_mutex_unlock(philo->kill);
}

int	get_ms(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - philo->beginning);
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
