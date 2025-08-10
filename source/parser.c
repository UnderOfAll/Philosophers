/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:26:37 by karocha-          #+#    #+#             */
/*   Updated: 2025/08/10 15:02:46 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_isspace(char c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	is_int(long nbr)
{
	return (INT_MIN <= nbr && nbr <= INT_MAX);
}

static size_t	ft_atoi_ph(const char *nptr, int *error)
{
	size_t	output;
	size_t	prev_output;

	output = 0;
	*error = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (!ft_isdigit(*nptr))
		*error = 1;
	while (ft_isdigit(*nptr))
	{
		prev_output = output;
		output = (output * 10) + (*nptr++ - '0');
		if (output < prev_output)
			*error = 1;
	}
	if (*nptr != '\0')
		*error = 1;
	return (output);
}

int	parse_args(int ac, char **av, t_table *table)
{
	int	error;

	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of args\n", 23), 1);
	table->num_of_philos = ft_atoi_ph(av[1], &error);
	if (error || table->num_of_philos < 1 || table->num_of_philos > 200)
		return (write(2, "Invalid number_of_philosophers\n", 31), 2);
	table->time_to_die = ft_atoi_ph(av[2], &error);
	if (error || table->time_to_die < 60)
		return (write(2, "Invalid time_to_die\n", 20), 3);
	table->time_to_eat = ft_atoi_ph(av[3], &error);
	if (error || table->time_to_eat < 60)
		return (write(2, "Invalid time_to_eat\n", 20), 4);
	table->time_to_sleep = ft_atoi_ph(av[4], &error);
	if (error || table->time_to_sleep < 60)
		return (write(2, "Invalid time_to_sleep\n", 22), 5);
	if (ac == 6)
	{
		table->meals_required_flag = 1;
		table->num_required_meals = ft_atoi_ph(av[5], &error);
		if (error || !is_int(ft_atoi_ph(av[5], &error)))
			return (write(2, "Invalid times philosophers must eat\n", 36), 6);
	}
	return (0);
}
