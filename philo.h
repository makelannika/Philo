/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:46:35 by amakela           #+#    #+#             */
/*   Updated: 2024/06/10 12:46:38 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int	philos;
	int	to_die;
	int	to_eat;
	int	to_sleep;
	int	meals;
	struct timeval beginning;
} t_data;

typedef struct s_philo
{
	struct timeval last_meal;
	int dead;
} t_philo;

#endif
