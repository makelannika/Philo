/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:33:39 by amakela           #+#    #+#             */
/*   Updated: 2024/06/30 18:48:27 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	lonely_philo(t_philo *philo)
{
	usleep(philo->to_die * 1000);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_lock(philo->kill);
	philo->dead = 1;
	pthread_mutex_unlock(philo->kill);
	return ;
}

static void	thinking(t_philo *philo)
{
	print_status_change("is thinking\n", philo);
}

static void	sleeping(t_philo *philo)
{
	print_status_change("is sleeping\n", philo);
	do_sleep(philo->to_sleep, philo);
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
	if (get_ms(philo) <= philo->last_meal + philo->to_die)
		philo->last_meal = get_ms(philo);
	if (philo->meals > 0)
		philo->meals--;
	print_status_change("is eating\n", philo);
	pthread_mutex_unlock(philo->eat);
	do_sleep(philo->to_eat, philo);
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
		pthread_mutex_lock(philo->kill);
		if (philo->dead)
		{
			pthread_mutex_unlock(philo->kill);
			return (ptr);
		}
		pthread_mutex_unlock(philo->kill);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
