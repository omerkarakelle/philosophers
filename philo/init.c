/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:46:47 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/25 14:52:52 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_philo *philo, int id)
{
	philo->id = id + 1;
	philo->state = STATE_THINKING;
	philo->last_eat = get_time_in_ms();
	philo->eat_time = 0;
}

void	ft_init_data(t_data *data)
{
	data->init_time = get_time_in_ms();
	data->using_forks = (int *)malloc(sizeof(int) * data->number_of_philos);
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	data->philos->philo = (pthread_t *)malloc(sizeof(pthread_t));
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philos);
	data->dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->last_eat_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->philos_that_ate = 0;
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) == -1)
			return (-1);
	}
	if (pthread_mutex_init(data->dead, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(data->print_mutex, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(data->last_eat_mutex, NULL) == -1)
		return (-1);
	return (0);
}
