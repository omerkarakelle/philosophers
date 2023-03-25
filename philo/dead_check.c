/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:21:00 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/25 17:09:43 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_deadcheck(void *philosophers)
{
	t_philo	*philo;
	int		a;

	philo = (t_philo *)philosophers;
	while (1)
	{
		pthread_mutex_lock(philo->data->last_eat_mutex);
		if (get_time_in_ms() - philo->last_eat >= philo->data->time_to_die)
		{
			a = ft_printinfo(philo, STATE_DEAD);
		}
		pthread_mutex_unlock(philo->data->last_eat_mutex);
		if (a == -1)
			return (NULL);
		usleep(10);
	}
	return (NULL);
}
