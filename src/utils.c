/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:37:33 by amakela           #+#    #+#             */
/*   Updated: 2024/06/19 20:03:17 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	free_all(pthread_mutex_t *forks, t_philo *philos, int count)
{
	destroy_mutexes(philos, count);
	free(forks);
	free(philos);
	return (1);
}

void	kill_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
		philos[i++].dead = 1;
}
