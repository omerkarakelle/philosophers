/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:15:08 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/26 15:28:13 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
		free(data->philos[i].philo);
	free(data->philos);
	free(data->forks);
	free(data->print_mutex);
	free(data->last_eat_mutex);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_mutex_destroy(data->forks + i);
	pthread_mutex_destroy(data->print_mutex);
	pthread_mutex_destroy(data->last_eat_mutex);
	return (0);
}

void	printmessage(t_philo *philo, int state)
{
	if (state == STATE_SLEEPING)
		printf("%lld\t%d is sleeping.\n", get_time_in_ms()
			- philo->data->init_time, philo->id);
	else if (state == STATE_THINKING)
		printf("%lld\t%d is thinking.\n", get_time_in_ms()
			- philo->data->init_time, philo->id);
	else if (state == STATE_EATING)
		printf("%lld\t%d is eating.\n", get_time_in_ms() - philo->data->init_time,
			philo->id);
	else if (state == STATE_DEAD)
		printf("%lld\t%d died\n", get_time_in_ms()
			- philo->data->init_time, philo->id);
	else if (state == STATE_FORK)
		printf("%lld\t%d has taken a fork.\n", get_time_in_ms()
			- philo->data->init_time, philo->id);
}

int	ft_printinfo(t_philo *philo, int state)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->data->print_mutex);
	if (state == STATE_EATING)
		philo->eat_time++;
	if (philo->eat_time == data->min_eat_limit && state == STATE_EATING)
		data->philos_that_ate++;
	if (philo->data->is_game_over == 1)
	{
		pthread_mutex_unlock(philo->data->print_mutex);
		return (-1);
	}
	printmessage(philo, state);
	if (data->philos_that_ate >= data->number_of_philos
		|| state == STATE_DEAD)
		philo->data->is_game_over = 1;
	pthread_mutex_unlock(philo->data->print_mutex);
	return (0);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int				i;
	long long int	num;
	int				sign;
	int				temp;

	sign = 1;
	num = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (ft_isdigit(str[i]))
	{
		temp = str[i++] - '0';
		num = num * 10 + temp;
		if (num * sign > 2147483647)
			return (-1);
		if (num * sign < -2147483648)
			return (0);
	}
	return (sign * num);
}
