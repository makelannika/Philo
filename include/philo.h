/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:46:35 by amakela           #+#    #+#             */
/*   Updated: 2024/07/01 13:06:07 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	kill;
}	t_mutex;

typedef struct s_philo
{
	int				num_of_philos;
	int				philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				meals;
	int				last_meal;
	int				dead;
	int				beginning;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*print;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*kill;
	pthread_t		thread;
}	t_philo;

int		arg_validation(int argc, char **argv);
int		ft_atoi(const char *str);
int		init_philos(t_philo **philos, int argc, char **argv);
int		init_mutexes(t_mutex *mutexes, t_philo *philos);
int		threading(pthread_mutex_t *forks, t_philo *philos, int count);
void	*supervise(void *ptr);
void	*routine(void *ptr);
int		philo_dead(t_philo *philo);
void	do_sleep(int time, t_philo *philo);
void	print_status_change(char *message, t_philo *philo);
int		get_ms(t_philo *philo);
int		free_philos_and_forks(pthread_mutex_t *forks,
			t_philo *philos, int count);

#endif
