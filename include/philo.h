/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:46:35 by amakela           #+#    #+#             */
/*   Updated: 2024/07/08 13:40:19 by amakela          ###   ########.fr       */
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
}	t_mutex;

typedef struct s_philo
{
	int				num_of_philos;
	int				philo;
	int				meals;
	int				dead;
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
	size_t			last_meal;
	size_t			beginning;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*print;
	pthread_mutex_t	eat;
	pthread_mutex_t	kill;
	pthread_t		thread;
}	t_philo;

int		arg_validation(int argc, char **argv);
int		ft_atoi(const char *str);
int		init_philos(t_philo **philos, int argc, char **argv);
int		init_mutexes(t_mutex *mutexes, t_philo *philos);
int		threading(t_mutex *mutexes, t_philo *philos);
void	*kill_philos(t_philo *philos, int count);
void	*supervise(void *ptr);
void	*routine(void *ptr);
int		philo_dead(t_philo *philo);
void	do_sleep(size_t time, t_philo *philo);
void	print_status_change(char *message, t_philo *philo);
size_t	get_ms(t_philo *philo);
void	destroy_forks(pthread_mutex_t *forks, int count);
void	destroy_kill(t_philo *philos, int count);
void	destroy_eat(t_philo *philos, int count);
int		free_and_destroy(t_mutex mutexes, t_philo *philos);

#endif
