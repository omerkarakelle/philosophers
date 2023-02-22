/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:28:17 by okarakel          #+#    #+#             */
/*   Updated: 2023/02/22 17:25:50 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thinking(t_philo *philo)
{
	philo->state = STATE_THINKING;
	printf("%lld %d is thinking.\n", get_time_in_us, philo->id);
}

void	ft_sleeping(t_philo *philo)
{
	if (get_time_in_ms() - philo->last_eat > philo->data->time_to_die)
	{
		printf("%lld %d died.\n", get_time_in_ms(), philo->id);
		exit(1);
	}
	philo->state = STATE_SLEEPING;
	if (get_time_in_ms() - philo->last_eat + philo->data->time_to_sleep > philo->data->time_to_die)
	{
		usleep(philo->data->time_to_die - get_time_in_ms() + philo->last_eat);
		printf("%lld %d is dead.\n", get_time_in_ms(), philo->id);
		exit(1);
	}
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_eating(t_philo *philo)
{
	t_data	*data = philo->data;
	int	f;

	while (1)
	{
		if (philo->id == 1 && (*(data->using_forks + data->number_of_philos - 1) == 0))
		{
			pthread_mutex_lock(&data->forks[data->number_of_philos - 1]);
			*(data->using_forks + data->number_of_philos - 1) = philo->id;
			printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
		}
		else if (data->using_forks[philo->id - 2] == 0)
		{
			pthread_mutex_lock(&data->forks[philo->id - 2]);
			data->using_forks[philo->id - 2] = philo->id;
			printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
		}
		if (data->using_forks[philo->id - 1] == 0)
		{
			pthread_mutex_lock(&data->forks[philo->id - 1]);
			data->using_forks[philo->id - 1] = philo->id;
			printf("%lld %d has taken a fork\n", get_time_in_ms(), philo->id);
		}
		if (philo->id == 1 && data->using_forks[data->number_of_philos - 1] == philo->id && data->using_forks[philo->id - 1] == philo->id)
		{
			philo->state = STATE_EATING;
			printf("%lld %d is eating.\n", get_time_in_us(), philo->id);
			philo->last_eat = get_time_in_ms();
			usleep(philo->data->time_to_eat * 1000);
			*(data->using_forks + data->number_of_philos - 1) = 0;
			data->using_forks[philo->id - 1] = 0;
			printf("%lld %d is sleeping.\n", get_time_in_ms(), philo->id);
			pthread_mutex_unlock(&data->forks[data->number_of_philos - 1]);
			pthread_mutex_unlock(&data->forks[philo->id - 1]);
			break ;
		}
		else if (data->using_forks[philo->id - 2] == philo->id && data->using_forks[philo->id - 1] == philo->id)
		{
			philo->state = STATE_EATING;
			printf("%lld %d is eating.\n", get_time_in_us(), philo->id);
			philo->last_eat = get_time_in_ms();
			usleep(philo->data->time_to_eat * 1000);
			data->using_forks[philo->id - 1] = 0;
			data->using_forks[philo->id - 2] = 0;
			printf("%lld %d is sleeping.\n", get_time_in_ms(), philo->id);
			pthread_mutex_unlock(&data->forks[philo->id - 1]);
			pthread_mutex_unlock(&data->forks[philo->id - 2]);
			break ;
		}
	}
}

void	*philo_loop(void *philoshopher)
{
	t_philo	*philo;

	philo = (t_philo *)philoshopher;
	while (1)
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (NULL);
}
