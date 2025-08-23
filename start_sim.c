/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuocak <yuocak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:46:31 by yuocak            #+#    #+#             */
/*   Updated: 2025/08/23 15:47:55 by yuocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	*monitor_thread(void *arg)
{
	(void)arg;
	return (NULL);
}
void	*philo_routine(void *arg)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)arg;
	while (philo->simulation_running == 0)
	{
		eating(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

int	join(t_philo_data *data)
{
	int	i;

	while (i < data->number_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			// hata kontorlü yapppp
			return (1);
		}
		i++;
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
		return (1);
	return (0);
}

int	start_sim(t_philo_data *data)
{
	int	i;

	i = 0;
	data->simulation_running = 1;
	data->start_time = get_time() * 1000; // Başlangıç zamanını set et
	while (i < data->number_philo)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			printf("Error: Failed to create philosopher thread %d\n", i);
			return (1);
		}
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_thread, data) != 0)
	{
		printf("Error\n");
		return (1);
	}
	if (join(data))
	{
		return (1);
	}
	return (0);
}
