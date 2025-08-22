/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuocak <yuocak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:01:13 by yuocak            #+#    #+#             */
/*   Updated: 2025/08/22 17:42:15 by yuocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)); // millisaniye döndür
}

int	init_philo(t_philo_data *data)
{
	int			i;
	long long	current_time;

	current_time = get_time() * 1000; // millisaniyeyi mikrosaniyeye çevir
	data->start_time = current_time;
	i = 0;
	while (i < data->number_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eaten_count = 0;
		data->philos[i].last_meal_time = current_time;
		data->philos[i].data = data;
		// Fork ataması: tek ID'ler için ters sıralama
		if (data->philos[i].id % 2 == 1) // Tek ID
		{
			data->philos[i].left_fork = &data->forks[(i + 1)
				% data->number_philo];
			data->philos[i].right_fork = &data->forks[i];
		}
		else // Çift ID
		{
			data->philos[i].left_fork = &data->forks[i];
			data->philos[i].right_fork = &data->forks[(i + 1)
				% data->number_philo];
		}
		i++;
	}
	return (0);
}

int	init_control_mutex(t_philo_data *data)
{
	if (pthread_mutex_init(&data->death_lock, NULL) != 0
		|| pthread_mutex_init(&data->print_lock, NULL) != 0
		|| pthread_mutex_init(&data->meal_lock, NULL) != 0)
	{
		clean_mutex(data);
		return (1);
	}
}

int	init_fork_mutex(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philo)
	{
		if (ptherad_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
				free(data->forks);
				free(data->philos);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	init_data(t_philo_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philo);
	if (data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->number_philo);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}
	if (init_fork_mutex(data))
	{
		return (1);
	}
	if (init_control_mutex(data))
	{
		return (1);
	}
	if (init_philo(data))
	{
	}
}
