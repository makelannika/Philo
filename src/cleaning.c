/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:05 by amakela           #+#    #+#             */
/*   Updated: 2024/07/06 22:05:29 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_eat(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&philos[i++].eat);
}

void	destroy_kill(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&philos[i++].kill);
}

void	destroy_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&forks[i++]);
	free(forks);
}

int	free_and_destroy(t_mutex mutexes, t_philo *philos)
{
	destroy_eat(philos, philos->num_of_philos);
	destroy_kill(philos, philos->num_of_philos);
	destroy_forks(mutexes.forks, philos->num_of_philos);
	free(philos);
	return (1);
}
