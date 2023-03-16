/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:21:00 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/16 18:48:17 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_deadcheck(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo *)philosophers;
	while (1)
	{
		if (get_time_in_ms() - philo->last_eat >= philo->data->time_to_die)
		{
			printf("%lld %d died.\n", get_time_in_ms() - philo->data->init_time, philo->id);
			exit(1);
		}
	}
}

int	is_anyone_dead(t_data *data)
{
	int	i;

	i = 0;
	if (data->deadnb == 1)
		i = 1;
	return (i);
}