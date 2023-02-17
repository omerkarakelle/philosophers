/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:41:07 by okarakel          #+#    #+#             */
/*   Updated: 2023/02/17 19:27:20 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_time_in_us()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_usec);
}

t_time	get_time_in_ms()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec/1000);
}

void	ft_init_philo(t_philo *philo, int id)
{
	philo->id = id + 1;
	philo->lh = 0;
	philo->rh = 0;
	philo->state = STATE_THINKING;
	philo->last_eat = get_time_in_ms();
}

int	ft_create_philos(t_data *data)
{
	int	i;

	i = -1;
	while(++i < data->number_of_philos)
	{
		ft_init_philo(data->philos + i, i);
		data->philos[i].philo = (pthread_t *)malloc(sizeof(pthread_t));
		data->philos[i].data = data;
		if (pthread_create(data->philos->philo + i, NULL, philo_loop, data->philos + i) != 0)
			return (-1);
		usleep(10);
	}
	return (0);
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (ft_check_args(argc, argv, &data) == -1)
		return (-1);
	printf("%d %d %d\n", data.number_of_philos, data.time_to_die, data.min_eat_limit);
	data.init_time = get_time_in_ms();
	printf("%lld\n", data.init_time);
	data.using_forks = (int *)malloc(sizeof(int) * data.number_of_philos);
	data.philos = malloc(sizeof(t_philo) * data.number_of_philos);
	data.philos->philo = (pthread_t *)malloc(sizeof(pthread_t));
	data.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.number_of_philos);
	init_mutex(&data);
	if (ft_create_philos(&data) == -1)
		return (ft_error("Error: Something happened while creating threads."));
	i = -1;
	while (++i < data.number_of_philos)
		pthread_join(*data.philos[i].philo, NULL);
	pthread_mutex_destroy(data.forks);
	return (0);
}
