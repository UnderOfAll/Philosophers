/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:26:37 by karocha-          #+#    #+#             */
/*   Updated: 2025/08/10 11:20:57 by karocha-         ###   ########.fr       */
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
	struct s_table	*table;
}				t_philo;

typedef struct s_table
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
}				t_table;

// parse_args.c
int			parse_args(int ac, char **av, t_table *table);

//utils.c
size_t		get_current_time(void);
int			ft_usleep(size_t milliseconds);
size_t		timestamp(t_table *table);
int			print_status(t_philo *philo, char *str, int force_print);

//init.c
int			init_table(int ac, char **av, t_table *table);

//threads.c
void		run_philos(t_table *table);

//thread_utils.c
int			threads_join(t_table *table);
int			meals_check(t_table *table);
int			is_dead(t_table *table);
void		destroy_locks(t_table *table);
void		meals_eaten_util(t_philo *philo);

#endif