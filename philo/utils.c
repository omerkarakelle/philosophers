/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:15:08 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/16 20:14:41 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printinfo(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	if (philo->state == STATE_SLEEPING)
		printf("%lld %d is sleeping.\n", get_time_in_ms() - data->init_time, philo->id);
	else if (philo->state == STATE_THINKING)
		printf("%lld %d is thinking.\n", get_time_in_ms() - data->init_time, philo->id);
	else if (philo->state == STATE_EATING)
		printf("%lld %d is eating.\n", get_time_in_ms() - data->init_time, philo->id);
	else if (philo->state == STATE_DEAD)
		printf("%lld %d died.\n", get_time_in_ms() - data->init_time, philo->id);
	else if (philo->state == STATE_FORK)
		printf("%lld %d has taken a fork.\n", get_time_in_ms() - data->init_time, philo->id);
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
