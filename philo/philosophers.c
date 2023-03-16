/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:28:17 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/16 20:17:49 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_thinking(t_philo *philo)
{
	if (is_anyone_dead(philo->data) == 1)
		return (-1);
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
	t_data	*data = philo->data;
	int		left;
	int		right;

	if (philo->id == 1)
		left = data->number_of_philos - 1;
	else
		left = philo->id - 2;
	right = philo->id - 1;
	while (1)
	{
		pthread_mutex_lock(&data->forks[left]);
		philo->state = STATE_FORK;
		ft_printinfo(philo);
		pthread_mutex_lock(&data->forks[right]);
		ft_printinfo(philo);
		philo->state = STATE_EATING;
		ft_printinfo(philo);
		philo->last_eat = get_time_in_ms();
		philo->eat_time++;
		if (philo->eat_time == data->min_eat_limit)
			data->adam++;
		if (data->adam >= data->number_of_philos)
			exit(1);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&data->forks[left]);
		pthread_mutex_unlock(&data->forks[right]);
		break ;
	}
	return (0);
}

void	*philo_loop(void *philoshopher)
{
	t_philo		*philo;
	pthread_t	pid;
	
	philo = (t_philo *)philoshopher;
	if (pthread_create(&pid, NULL, &ft_deadcheck, philoshopher) != 0)
			return (-1);
	while (1)
	{
		if (ft_eating(philo) == -1)
			break;
		if (ft_sleeping(philo) == -1)
			break;
		if (ft_thinking(philo) == -1)
			break;
	}
	pthread_join(pid, NULL);
	return (NULL);
}
