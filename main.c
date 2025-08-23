/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuocak <yuocak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:41:07 by yuocak            #+#    #+#             */
/*   Updated: 2025/08/23 14:13:17 by yuocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	init_struct(t_philo_data *data)
{
	data->number_philo = 0;
	data->time_to_die = 0;
	data->time_to_sleep = 0;
	data->time_to_eat = 0;
	data->must_eat_count = -1;
	data->start_time = 0;
	data->simulation_running = 1;
	data->all_eaten = 0;
	data->forks = NULL;
	data->philos = NULL;
}

int	main(int argc, char **argv)
{
	t_philo_data	data;

	init_struct(&data);
	if (check_arguments(argc, argv, &data))
		return (1);
	if (init_data(&data) != 0)
	{
		printf("Error: Failed to initialize data\n");
		return (1);
	}
	// Burada philosopher thread'lerini başlatacaksın
	start_sim(&data);
	clean_mutex(&data);
	return (0);
}
