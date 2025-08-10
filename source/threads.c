/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:26:37 by karocha-          #+#    #+#             */
/*   Updated: 2025/08/10 16:20:35 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	has_eaten_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eaten_enough_lock);
	if (philo->has_eaten_enough)
	{
		pthread_mutex_unlock(&philo->table->eaten_enough_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->eaten_enough_lock);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&(philo->table->forks_lock[philo->left_fork]));
	else
		pthread_mutex_lock(&(philo->table->forks_lock[philo->right_fork]));
	print_status(philo, "has taken a fork", 0);
	if (philo->table->num_of_philos == 1)
		return (pthread_mutex_unlock(
				&(philo->table->forks_lock[philo->left_fork])), 1);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&(philo->table->forks_lock[philo->right_fork]));
	else
		pthread_mutex_lock(&(philo->table->forks_lock[philo->left_fork]));
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->table->last_meal_lock);
	philo->time_of_last_meal = timestamp(philo->table);
	pthread_mutex_unlock(&philo->table->last_meal_lock);
	print_status(philo, "is eating", 0);
	ft_usleep(philo->table->time_to_eat);
	meals_eaten_util(philo);
	pthread_mutex_unlock(&(philo->table->forks_lock[philo->right_fork]));
	pthread_mutex_unlock(&(philo->table->forks_lock[philo->left_fork]));
	print_status(philo, "is sleeping", 0);
	ft_usleep(philo->table->time_to_sleep);
	print_status(philo, "is thinking", 0);
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (is_dead(table))
			return (NULL);
		if (table->meals_required_flag && meals_check(table))
		{
			pthread_mutex_lock(&table->write_lock);
			table->finished = 1;
			return (pthread_mutex_unlock(&table->write_lock), NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat);
	while (1)
	{
		if (has_eaten_check(philo))
			return (NULL);
		if (eat(philo))
		{
			pthread_mutex_lock(&philo->table->write_lock);
			philo->table->finished = 1;
			return (pthread_mutex_unlock(&philo->table->write_lock), NULL);
		}
		pthread_mutex_lock(&philo->table->write_lock);
		if (philo->table->finished == 1)
			return (pthread_mutex_unlock(&philo->table->write_lock), NULL);
		pthread_mutex_unlock(&philo->table->write_lock);
		if (philo->table->num_of_philos % 2 == 1)
			ft_usleep((philo->table->time_to_eat * 2)
				- (philo->table->time_to_sleep));
	}
	return (NULL);
}

void	run_philos(t_table *table)
{
	int	i;

	pthread_create(&table->monitor, NULL, monitor, (void *)table);
	i = -1;
	while (++i < table->num_of_philos)
	{
		pthread_mutex_lock(&table->last_meal_lock);
		table->philos[i].time_of_last_meal = timestamp(table);
		pthread_create(&table->philos[i].thread, NULL, routine,
			(void *)&table->philos[i]);
		pthread_mutex_unlock(&table->last_meal_lock);
	}
}
