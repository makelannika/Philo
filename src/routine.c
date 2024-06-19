/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:33:39 by amakela           #+#    #+#             */
/*   Updated: 2024/06/19 21:33:47 by amakela          ###   ########.fr       */
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
	pthread_mutex_lock(philo->print);
	if (!philo->dead)
		printf("%d Philo %d is thinking 💭\n", get_ms(), philo->philo);
	pthread_mutex_unlock(philo->print);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (!philo->dead)
		printf("%d Philo %d is sleeping 💤\n", get_ms(), philo->philo);
	pthread_mutex_unlock(philo->print);
	if (!philo->dead)
		usleep(philo->to_sleep * 1000);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(philo->print);
	if (!philo->dead)
		printf("%d Philo %d has taken left fork 🍴\n", get_ms(), philo->philo);
	pthread_mutex_unlock(philo->print);
	if (philo->num_of_philos == 1)
		return (lonely_philo(philo));
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(philo->print);
	if (!philo->dead)
		printf("%d Philo %d has taken right fork 🍴\n", get_ms(), philo->philo);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->eat);
	if (get_ms() <= philo->last_meal + philo->to_die)
		philo->last_meal = get_ms();
	pthread_mutex_unlock(philo->eat);
	pthread_mutex_lock(philo->print);
	if (!philo->dead)
		printf("%d Philo %d is eating 🍝\n", get_ms(), philo->philo);
	pthread_mutex_unlock(philo->print);
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
		philo->meals--;
		if (!philo->meals)
			return (ptr);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
