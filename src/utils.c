/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:37:33 by amakela           #+#    #+#             */
/*   Updated: 2024/07/06 20:24:18 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->kill);
	if (philo->dead)
	{
		pthread_mutex_unlock(&philo->kill);
		return (1);
	}
	pthread_mutex_unlock(&philo->kill);
	return (0);
}

void	do_sleep(size_t time, t_philo *philo)
{
	size_t	end;
	size_t	death;

	end = get_ms(philo) + time;
	death = philo->last_meal + philo->to_die;
	if (!philo_dead(philo))
	{
		while (get_ms(philo) < end && get_ms(philo) < death)
			usleep(500);
	}
}

void	print_status_change(char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (!philo_dead(philo))
		printf("%zu %d %s", get_ms(philo), philo->philo, message);
	pthread_mutex_unlock(philo->print);
}

size_t	get_ms(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - philo->beginning);
}
