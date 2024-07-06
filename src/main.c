/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:36:11 by amakela           #+#    #+#             */
/*   Updated: 2024/07/06 15:26:19 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_mutex	mutexes;

	philos = NULL;
	mutexes = (t_mutex){0};
	if (arg_validation(argc, argv))
		return (1);
	if (init_philos(&philos, argc, argv))
		return (1);
	if (init_mutexes(&mutexes, philos))
		return (1);
	if (threading(philos))
		return (1);
	free_and_destroy(mutexes, philos);
	return (0);
}
