/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:41:07 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/26 16:26:48 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_time_in_us(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_usec);
}

t_time	get_time_in_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_create_philos(t_data *data, int c)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (i % 2 == c)
			continue ;
		ft_init_philo(data->philos + i, i);
		data->philos[i].philo = (pthread_t *)malloc(sizeof(pthread_t));
		data->philos[i].data = data;
		if (pthread_create(data->philos[i].philo, NULL, philo_loop,
				data->philos + i) != 0)
			return (-1);
		usleep(1000);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (ft_check_args(argc, argv, &data) == -1)
		return (-1);
	ft_init_data(&data);
	init_mutex(&data);
	if (ft_create_philos(&data, 1) == -1)
		return (ft_error("Error: Something happened while creating threads."));
	if (ft_create_philos(&data, 0) == -1)
		return (ft_error("Error: Something happened while creating threads."));
	i = -1;
	while (++i < data.number_of_philos)
		pthread_join(*data.philos[i].philo, NULL);
	return (ft_exit(&data));
}
