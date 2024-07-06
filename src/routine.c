/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:33:39 by amakela           #+#    #+#             */
/*   Updated: 2024/07/06 20:20:57 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	lonely_philo(t_philo *philo)
{
	do_sleep(philo->to_die, philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_lock(&philo->kill);
	philo->dead = 1;
	pthread_mutex_unlock(&philo->kill);
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
	pthread_mutex_lock(&philo->eat);
	if (get_ms(philo) < philo->last_meal + philo->to_die)
	{
		philo->last_meal = get_ms(philo);
		print_status_change("is eating\n", philo);
	}
	pthread_mutex_unlock(&philo->eat);
	do_sleep(philo->to_eat, philo);
	pthread_mutex_lock(&philo->eat);
	if (philo->meals > 0)
		philo->meals--;
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	print_status_change("is thinking\n", philo);
	if (philo->philo % 2 == 0)
		usleep(5000);
	while (1)
	{
		if (philo_dead(philo))
			return (ptr);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
