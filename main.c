/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuocak <yuocak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:41:07 by yuocak            #+#    #+#             */
/*   Updated: 2025/08/22 15:52:35 by yuocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_philo_data	data;

	if (check_arguments(argc, argv))
		return (1);
	if (init_data(&data) != 0)
	{
		return (1);
	}
}
