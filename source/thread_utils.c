/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:26:37 by karocha-          #+#    #+#             */
/*   Updated: 2025/08/10 15:56:59 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	threads_join(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (write(2, "pthread_join error\n", 19), 1);
	if (pthread_join(table->monitor, NULL) != 0)
		return (write(2, "pthread_join error\n", 19), 1);
	return (0);
}

int	meals_check(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_lock(&table->eaten_enough_lock);
		if (!(table->philos[i].has_eaten_enough))
			return (pthread_mutex_unlock(&table->eaten_enough_lock), 0);
		pthread_mutex_unlock(&table->eaten_enough_lock);
	}
	usleep(10);
	return (1);
}

int	is_dead(t_table *table)
{
	size_t	dead_time;
	int		i;

	i = -1;
	if (timestamp(table) < table->time_to_die)
		dead_time = 0;
	else
		dead_time = timestamp(table) - table->time_to_die;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_lock(&table->last_meal_lock);
		if (table->philos[i].time_of_last_meal <= dead_time && dead_time != 0)
		{
			print_status(&(table->philos[i]), "died", 1);
			pthread_mutex_lock(&table->write_lock);
			table->finished = 1;
			pthread_mutex_unlock(&table->last_meal_lock);
			return (pthread_mutex_unlock(&table->write_lock), 1);
		}
		pthread_mutex_unlock(&table->last_meal_lock);
	}
	return (0);
}

void	destroy_locks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philos)
		pthread_mutex_destroy(&(table->forks_lock[i]));
	pthread_mutex_destroy(&(table->write_lock));
}

void	meals_eaten_util(t_philo *philo)
{
	philo->meals_eaten += 1;
	pthread_mutex_lock(&philo->table->eaten_enough_lock);
	if (!philo->has_eaten_enough
		&& (philo->meals_eaten == philo->table->num_required_meals))
		philo->has_eaten_enough = 1;
	pthread_mutex_unlock(&philo->table->eaten_enough_lock);
}
