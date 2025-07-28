/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:09:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/09/06 15:48:44 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&(philo->data->forks_lock[philo->left_fork]));
	else
		pthread_mutex_lock(&(philo->data->forks_lock[philo->right_fork]));
	print_status(philo, "has taken a fork", 0);
	if (philo->data->num_of_philos == 1)
		return (pthread_mutex_unlock(
				&(philo->data->forks_lock[philo->left_fork])), 1);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&(philo->data->forks_lock[philo->right_fork]));
	else
		pthread_mutex_lock(&(philo->data->forks_lock[philo->left_fork]));
	print_status(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->data->last_meal_lock);
	philo->time_of_last_meal = timestamp(philo->data);
	pthread_mutex_unlock(&philo->data->last_meal_lock);
	print_status(philo, "is eating", 0);
	ft_usleep(philo->data->time_to_eat);
	meals_eaten_util(philo);
	pthread_mutex_unlock(&(philo->data->forks_lock[philo->right_fork]));
	pthread_mutex_unlock(&(philo->data->forks_lock[philo->left_fork]));
	print_status(philo, "is sleeping", 0);
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, "is thinking", 0);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (is_dead(data))
			return (NULL);
		if (data->meals_required_flag && meals_check(data))
		{
			pthread_mutex_lock(&data->write_lock);
			data->finished = 1;
			return (pthread_mutex_unlock(&data->write_lock), NULL);
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
		ft_usleep(philo->data->time_to_eat);
	while (1)
	{
		if (eat(philo))
		{
			pthread_mutex_lock(&philo->data->write_lock);
			philo->data->finished = 1;
			return (pthread_mutex_unlock(&philo->data->write_lock), NULL);
		}
		pthread_mutex_lock(&philo->data->write_lock);
		if (philo->data->finished == 1)
			return (pthread_mutex_unlock(&philo->data->write_lock), NULL);
		pthread_mutex_unlock(&philo->data->write_lock);
		if (philo->data->num_of_philos % 2 == 1)
			ft_usleep((philo->data->time_to_eat * 2)
				- (philo->data->time_to_sleep));
	}
	return (NULL);
}

void	run_philos(t_data *data)
{
	int	i;

	pthread_create(&data->monitor, NULL, monitor, (void *)data);
	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->last_meal_lock);
		data->philos[i].time_of_last_meal = timestamp(data);
		pthread_create(&data->philos[i].thread, NULL, routine,
			(void *)&data->philos[i]);
		pthread_mutex_unlock(&data->last_meal_lock);
	}
}
