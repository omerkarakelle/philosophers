/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:28:17 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/25 18:43:05 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_routine(t_philo *philo, t_data *data, int left, int right)
{
	int	a;

	pthread_mutex_lock(&data->forks[left]);
	a = ft_printinfo(philo, STATE_FORK);
	if (left == right)
	{
		usleep(data->time_to_die * 1000);
		return (-1);
	}
	pthread_mutex_lock(&data->forks[right]);
	a = ft_printinfo(philo, STATE_FORK);
	a = ft_printinfo(philo, STATE_EATING);
	pthread_mutex_lock(data->last_eat_mutex);
	philo->last_eat = get_time_in_ms();
	pthread_mutex_unlock(data->last_eat_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[left]);
	pthread_mutex_unlock(&data->forks[right]);
	return (a);
}

int	ft_thinking(t_philo *philo)
{
	return (ft_printinfo(philo, STATE_THINKING));
}

int	ft_sleeping(t_philo *philo)
{
	int	a;

	a = ft_printinfo(philo, STATE_SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
	return (a);
}

int	ft_eating(t_philo *philo)
{
	t_data	*data;
	int		left;
	int		right;

	data = philo->data;
	if (philo->id == 1)
		left = data->number_of_philos - 1;
	else
		left = philo->id - 2;
	right = philo->id - 1;
	return (eating_routine(philo, data, left, right));
}

void	*philo_loop(void *philoshopher)
{
	t_philo		*philo;
	pthread_t	pid;

	philo = (t_philo *)philoshopher;
	if (pthread_create(&pid, NULL, &ft_deadcheck, philoshopher) != 0)
		return (NULL);
	while (1)
	{
		if (ft_eating(philo) == -1)
			break ;
		if (ft_sleeping(philo) == -1)
			break ;
		if (ft_thinking(philo) == -1)
			break ;
	}
	pthread_join(pid, NULL);
	sleep(1);
	return (NULL);
}
