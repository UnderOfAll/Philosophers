/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:09:58 by thopgood          #+#    #+#             */
/*   Updated: 2024/09/06 15:48:44 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(ac, av, &data) != 0)
		return (1);
	data.start_time = get_current_time();
	run_philos(&data);
	threads_join(&data);
	destroy_locks(&data);
	return (0);
}
