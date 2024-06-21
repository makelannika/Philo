/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:33:39 by amakela           #+#    #+#             */
/*   Updated: 2024/06/21 16:16:29 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	lonely_philo(t_philo *philo)
{
	usleep(philo->to_die * 1000);
	pthread_mutex_unlock(philo->fork_l);
	philo->dead = 1;
	return ;
}

static void	thinking(t_philo *philo)
{
	print_status_change("is thinking\n", philo);
}

static void	sleeping(t_philo *philo)
{
	print_status_change("is sleeping\n", philo);
	if (!philo->dead)
		usleep(philo->to_sleep * 1000);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_status_change("has taken a fork\n", philo);
	if (philo->num_of_philos == 1)
		return (lonely_philo(philo));
	pthread_mutex_lock(philo->fork_r);
	print_status_change("has taken a fork\n", philo);
	pthread_mutex_lock(philo->eat);
	if (get_ms() <= philo->last_meal + philo->to_die)
		philo->last_meal = get_ms();
	if (philo->meals > 0)
		philo->meals--;
	pthread_mutex_unlock(philo->eat);
	print_status_change("is eating\n", philo);
	if (!philo->dead)
		usleep(philo->to_eat * 1000);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->philo % 2 != 0)
		usleep(500);
	while (1)
	{
		if (philo->dead)
			return (ptr);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
