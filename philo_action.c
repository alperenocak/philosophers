/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuocak <yuocak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:50:11 by yuocak            #+#    #+#             */
/*   Updated: 2025/08/23 16:29:00 by yuocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	sensitive_sleep(t_philo_data *philo, long long sleep_time)
{
	long long	start_time;
	long long	elapsed;

	start_time = get_time() * 1000;
	while (philo->simulation_running)
	{
		elapsed = (get_time() * 1000) - start_time;
		if (elapsed >= sleep_time)
			break ;
		usleep(100);
	}
}

void	take_forks(t_philo *philo)
{
	if (!philo || !philo->left_fork || !philo->right_fork)
	{
		printf("Error: NULL fork pointer!\n");
		return ;
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}
void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time() * 1000;
	pthread_mutex_unlock(&philo->data->meal_lock);
	sensitive_sleep(philo->data, philo->data->time_to_eat * 1000);
	philo->eaten_count++;
	put_forks(philo);
}

void	think(t_philo *philo)
{
	long long	think_time;

	print_status(philo, "is thinking");
	think_time = (philo->data->time_to_eat - philo->data->time_to_sleep) / 2;
	if (think_time > 0)
		sensitive_sleep(philo->data, think_time * 1000);
	while (!forks_avail(philo) && philo->data->simulation_running)
		sensitive_sleep(philo->data, 100);
}

void	sleeping(t_philo *philo)
{
	long long	start;

	print_status(philo, "is sleeping");
	sensitive_sleep(philo->data, philo->data->time_to_sleep * 1000);
	start = get_time() * 1000;
	while ((get_time() * 1000 - start) < philo->data->time_to_sleep)
	{
		usleep(200);
		if (philo->data->simulation_running)
			break ;
	}
}

void	print_status(t_philo *philo, char *message)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->simulation_running)
	{
		current_time = (get_time() * 1000) - philo->data->start_time;
		printf("%lld %d %s\n", current_time / 1000, philo->id, message);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	forks_avail(t_philo *philo)
{
	int	left_available;
	int	right_available;

	left_available = 0;
	right_available = 0;
	if (pthread_mutex_trylock(philo->left_fork) == 0)
	{
		left_available = 1;
		pthread_mutex_unlock(philo->left_fork);
	}
	if (pthread_mutex_trylock(philo->right_fork) == 0)
	{
		right_available = 1;
		pthread_mutex_unlock(philo->right_fork);
	}
	return (left_available && right_available);
}
