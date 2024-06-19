/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:36:11 by amakela           #+#    #+#             */
/*   Updated: 2024/06/19 16:48:08 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;

	philos = NULL;
	forks = NULL;
	if (arg_validation(argc, argv))
		return (1);
	if (init_philos(&philos, argc, argv))
		return (1);
	if (init_mutexes(&forks, &print, philos))
		return (1);
	if (threading(forks, philos, philos->num_of_philos))
		return (1);
	return (0);
}
