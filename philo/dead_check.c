/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:21:00 by okarakel          #+#    #+#             */
/*   Updated: 2023/02/26 19:43:18 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_deadcheck(t_philo *philo)
{
		
	printf("%lld %d died\n", get_time_in_ms(), philo->id);
	
}

int	is_anyone_dead(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->dead);
	if (data->deadnb == 1)
		i = 1;
	pthread_mutex_unlock(data->dead);
	return (i);
}