/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:36:11 by amakela           #+#    #+#             */
/*   Updated: 2024/06/18 13:19:36 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	overflow(int neg)
{
	if (neg == -1)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;
	int		neg;
	long	prev;

	i = 0;
	nbr = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i ++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = nbr;
		nbr = 10 * nbr + str[i++] - '0';
		if (prev > nbr)
			return (overflow(neg));
	}
	return ((int)nbr * neg);
}

int	check_values(char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (write(2, "invalid number of philosophers\n", 31));
	if (ft_atoi(argv[2]) < 1)
		return (write(2, "invalid time to die\n", 20));
	if (ft_atoi(argv[3]) < 1)
		return (write(2, "invalid time to eat\n", 20));
	if (ft_atoi(argv[4]) < 1)
		return (write(2, "invalid time to sleep\n", 22));
	if (argv[5] && ft_atoi(argv[5]) == 0)
		return (1);
	return (0);
}

int	arg_validation(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
		return (write(2, "invalid amount of arguments\n", 28));
	while (argv[i])
	{
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (write(2, "arguments need to be numbers only\n", 34));
			j++;
		}
		i++;
		j = 0;
	}
	return (check_values(argv));
}

int	get_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	lonely_philo(t_philo *philo)
{
	usleep(philo->to_die * 1000);
	pthread_mutex_unlock(philo->fork_l);
	philo->dead = 1;
	return ;
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (!philo->dead)
		printf("%d Philo %d is thinking 💭\n", get_ms(), philo->philo);
	pthread_mutex_unlock(philo->print);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	if (!philo->dead)
		printf("%d Philo %d is sleeping 💤\n", get_ms(), philo->philo);
	pthread_mutex_unlock(philo->print);
	if (!philo->dead)
		usleep(philo->to_sleep * 1000);
}

void	eating(t_philo *philo)
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
	philo->last_meal = get_ms();
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

void	destroy_forks(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		pthread_mutex_destroy(philos[i].fork_l);
		pthread_mutex_destroy(philos[i].fork_r);
		i++;
	}
}

int	init_mutexes(pthread_mutex_t *forks, pthread_mutex_t *print, t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i++], NULL))
			return (1);
	}
	if (pthread_mutex_init(print, NULL))
		return (1);
	i = 0;
	while (i < count - 1)
	{
		philos[i].fork_l = &forks[i];
		philos[i].fork_r = &forks[i + 1];
		philos[i].print = print;
		i++;
	}
	philos[i].fork_l = &forks[i];
	philos[i].fork_r = &forks[0];
	philos[i].print = print;
	return (0);
}

void	init_philos(t_philo *philos, int argc, char **argv)
{
	int		i;
	t_philo	philo;

	i = 0;
	philo = (t_philo){0};
	philo.num_of_philos = ft_atoi(argv[1]);
	philo.dead = 0;
	philo.to_die = ft_atoi(argv[2]);
	philo.to_eat = ft_atoi(argv[3]);
	philo.to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.meals = ft_atoi(argv[5]);
	else
		philo.meals = -1;
	while (i < philo.num_of_philos)
	{
		philo.philo = i + 1;
		philos[i++] = philo;
	}
}

void	kill_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
		philos[i++].dead = 1;
}

void	*supervise(void *ptr)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)ptr;
	while (i < philos->num_of_philos)
	{
		philos[i++].last_meal = get_ms();
		printf("%d Philo %d started\n", philos[i - 1].last_meal, philos[i - 1].philo);
	}
	while (1)
	{
		if (i == philos->num_of_philos)
			i = 0;
		if (!philos[i].meals)
			return (NULL);
		if (get_ms() >= philos[i].last_meal + philos[i].to_die)
		{
			philos[i].dead = 1;
			printf("%d Philo %d died\n", get_ms(), philos[i].philo);
		}
		if (philos[i].dead)
		{
			kill_philos(philos, philos->num_of_philos);
			return (NULL);
		}
		i++;
	}
}

int	simulation(int argc, char **argv, int count)
{
	int				i;
	t_philo			philos[count];
	pthread_mutex_t	forks[count];
	pthread_mutex_t	print;
	pthread_t		supervisor;

	i = 0;
	init_philos(philos, argc, argv);
	if (init_mutexes(forks, &print, philos, count))
		return (1);
	if (pthread_create(&supervisor, NULL, &supervise, philos) != 0)
	{
		destroy_forks(philos, count);
		return (write(2, "creating threads failed\n", 24));
	}
	while (i < count)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			destroy_forks(philos, count);
			return (write(2, "creating threads failed\n", 24));
		}
		i++;
	}
	i = 0;
	if (pthread_join(supervisor, NULL) != 0)
	{
		destroy_forks(philos, count);
		return (write(2, "joining threads failed\n", 23));
	}
	while (i < count)
	{
		if (pthread_join(philos[i++].thread, NULL) != 0)
		{
			destroy_forks(philos, count);
			return (write(2, "joining threads failed\n", 23));
		}
	}
	destroy_forks(philos, count);
	return (0);
}

int	main(int argc, char **argv)
{
	if (arg_validation(argc, argv))
		return (1);
	if (simulation(argc, argv, ft_atoi(argv[1])))
		return (1);
	return (0);
}
