/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuocak <yuocak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:55:20 by yuocak            #+#    #+#             */
/*   Updated: 2025/08/23 13:18:43 by yuocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	is_valid_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	trimmed_and_valid_value(int argc, char **argv)
{
	int		i;
	char	*trimmed;

	i = 1;
	while (i < argc)
	{
		trimmed = ft_strtrim(argv[i], " \t\n\r");
		if (!trimmed || !is_valid_number(trimmed))
		{
			if (trimmed)
				free(trimmed);
			printf("Error: Argument %d is not a valid number\n", i);
			return (1);
		}
		argv[i] = trimmed;
		i++;
	}
	return (0);
}

void	parse_arguments(char **argv, int argc, t_philo_data *data)
{
	data->number_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
}

int	check_arguments(int argc, char **argv, t_philo_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die");
		printf("time_to_eat time_to_sleep");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (trimmed_and_valid_value(argc, argv))
		return (1);
	parse_arguments(argv, argc, data);
	return (0);
}
