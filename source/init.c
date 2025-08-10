/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:26:37 by karocha-          #+#    #+#             */
/*   Updated: 2025/08/10 11:14:09 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	initialise_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->num_of_philos;
		table->philos[i].table = table;
	}
	return (0);
}

int	initialize_mutexes(pthread_mutex_t *mutexes, int count)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < count)
	{
		ret = pthread_mutex_init(&mutexes[i], NULL);
		if (ret != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&mutexes[i]);
			return (ret);
		}
	}
	return (0);
}

int	init_table(int ac, char **av, t_table *table)
{
	int	err;

	memset(table, 0, sizeof(*table));
	if (parse_args(ac, av, table) != 0)
		return (1);
	if (table->meals_required_flag && table->num_required_meals == 0)
		return (5);
	err = pthread_mutex_init(&table->write_lock, NULL);
	if (err != 0)
		return (write(2, "Error initialising mutex\n", 25), 2);
	err = pthread_mutex_init(&table->last_meal_lock, NULL);
	if (err != 0)
		return (write(2, "Error initialising mutex\n", 25), 2);
	err = pthread_mutex_init(&table->eaten_enough_lock, NULL);
	if (err != 0)
		return (write(2, "Error initialising mutex\n", 25), 2);
	err = initialize_mutexes(table->forks_lock, table->num_of_philos);
	if (err != 0)
		return (write(2, "Error initialising mutex\n", 25), 3);
	if (initialise_philos(table) != 0)
		return (4);
	return (0);
}
