/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:10:08 by thopgood          #+#    #+#             */
/*   Updated: 2024/09/09 15:04:22 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define MAX_PHILOSOPHERS 200

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				has_eaten_enough;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	size_t			time_of_last_meal;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_required_flag;
	int				num_required_meals;
	size_t			start_time;
	pthread_t		monitor;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks_lock[MAX_PHILOSOPHERS];
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	eaten_enough_lock;
	t_philo			philos[MAX_PHILOSOPHERS];
	int				finished;
}				t_data;

// parse_args.c
int			parse_args(int ac, char **av, t_data *data);

//utils.c
size_t		get_current_time(void);
int			ft_usleep(size_t milliseconds);
size_t		timestamp(t_data *data);
int			print_status(t_philo *philo, char *str, int force_print);

//init.c
int			init_data(int ac, char **av, t_data *data);

//threads.c
void		run_philos(t_data *data);

//thread_utils.c
int			threads_join(t_data *data);
int			meals_check(t_data *data);
int			is_dead(t_data *data);
void		destroy_locks(t_data *data);
void		meals_eaten_util(t_philo *philo);

#endif