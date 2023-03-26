/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarakel <omerlutfu.k34@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:39:22 by okarakel          #+#    #+#             */
/*   Updated: 2023/03/26 16:27:07 by okarakel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define STATE_EATING 1
# define STATE_SLEEPING 2
# define STATE_THINKING 3
# define STATE_DEAD 4
# define STATE_FORK 5

typedef long long	t_time;
struct				s_data;

typedef struct s_philo
{
	int				id;
	int				state;
	int				eat_time;
	t_time			last_eat;
	pthread_t		*philo;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				philos_that_ate;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat_limit;
	int				is_game_over;
	t_time			init_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*last_eat_mutex;
	t_philo			*philos;
}	t_data;

int		ft_check_args(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_error(char *str);
void	*philo_loop(void *data);
t_time	get_time_in_ms(void);
t_time	get_time_in_us(void);
void	*ft_deadcheck(void *philo);
int		ft_printinfo(t_philo *philo, int state);
void	ft_init_philo(t_philo *philo, int id);
void	ft_init_data(t_data *data);
int		init_mutex(t_data *data);
int		ft_exit(t_data *data);

#endif