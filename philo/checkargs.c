/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:09:58 by okarakel          #+#    #+#             */
/*   Updated: 2023/02/12 18:47:31 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	printf("%s", str);
	return (-1);
}

int	ft_check_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (ft_error("Error: Number of arguments is not satisfied.\n"));
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_die = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->min_eat_limit = -1;
	else
		data->min_eat_limit = ft_atoi(argv[5]);
	if (data->number_of_philos < 0 || data->time_to_die < 0 || data->time_to_die < 0 || data->time_to_sleep < 0 || (argc == 6 && data->min_eat_limit <= 0))
		return (ft_error("Error: Check the arguments.\n"));
	return (0);
}
