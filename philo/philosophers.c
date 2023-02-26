/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:28:17 by okarakel          #+#    #+#             */
/*   Updated: 2023/02/26 20:36:45 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_thinking(t_philo *philo)
{
	if (is_anyone_dead(philo->data) == 1)
		return ;
	philo->state = STATE_THINKING;
	printf("%lld %d is thinking.\n", get_time_in_ms() - philo->data->init_time, philo->id);
}

void	ft_sleeping(t_philo *philo)
{
	if (is_anyone_dead(philo->data) == 1)
		return ;
	if (get_time_in_ms() - philo->last_eat > philo->data->time_to_die)
	{
		philo->data->deadnb = 1;
		printf("%lld %d died.\n", get_time_in_ms() - philo->data->init_time, philo->id);
		exit(1);
	}
	printf("%lld %d is sleeping.\n", get_time_in_ms() - philo->data->init_time, philo->id);
	if (get_time_in_ms() - philo->last_eat + philo->data->time_to_sleep > philo->data->time_to_die)
	{
		usleep(philo->data->time_to_die - get_time_in_ms() + philo->last_eat);
		philo->data->deadnb = 1;
		printf("%lld %d died.\n", get_time_in_ms() - philo->data->init_time, philo->id);
		exit(1);
	}
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_eating(t_philo *philo)
{
	t_data	*data = philo->data;
	int	left;
	int	right;

	if (philo->id == 1)
		left = data->number_of_philos - 1;
	else
		left = philo->id - 2;
	right = philo->id - 1;
	if (is_anyone_dead(data) == 1)
		return ;
	while (1)
	{
		pthread_mutex_lock(&data->forks[right]);
		printf("%lld %d has taken a fork\n", get_time_in_ms() - data->init_time, philo->id);
		pthread_mutex_lock(&data->forks[left]);
		printf("%lld %d has taken a fork\n", get_time_in_ms() - data->init_time, philo->id);
		printf("%lld %d is eating.\n", get_time_in_ms() - data->init_time, philo->id);
		philo->last_eat = get_time_in_ms();
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&data->forks[left]);
		pthread_mutex_unlock(&data->forks[right]);
		break ;
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
