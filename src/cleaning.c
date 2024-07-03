/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:05 by amakela           #+#    #+#             */
/*   Updated: 2024/07/01 13:02:26 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
