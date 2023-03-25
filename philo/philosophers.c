/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:28:17 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/25 16:17:52 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_routine(t_philo *philo, t_data *data, int left, int right)
{
	pthread_mutex_lock(&data->forks[left]);
	philo->state = STATE_FORK;
	ft_printinfo(philo);
	pthread_mutex_lock(&data->forks[right]);
	ft_printinfo(philo);
	philo->state = STATE_EATING;
	philo->eat_time++;
	if (philo->eat_time == data->min_eat_limit)
		data->philos_that_ate++;
	if (data->philos_that_ate >= data->number_of_philos)
	{
		pthread_mutex_lock(data->print_mutex);
		printf("%lld\t%d is eating.\n", get_time_in_ms() - data->init_time,
			philo->id);
		exit(1);
	}
	ft_printinfo(philo);
	pthread_mutex_lock(data->last_eat_mutex);
	philo->last_eat = get_time_in_ms();
	pthread_mutex_unlock(data->last_eat_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[left]);
	pthread_mutex_unlock(&data->forks[right]);
	return (0);
}

int	ft_thinking(t_philo *philo)
{
	philo->state = STATE_THINKING;
	ft_printinfo(philo);
	return (0);
}

int	ft_sleeping(t_philo *philo)
{
	philo->state = STATE_SLEEPING;
	ft_printinfo(philo);
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
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
	return (eating_routine(philo, data, left, right) == -1);
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
	return (NULL);
}
