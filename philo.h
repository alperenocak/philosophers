/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuocak <yuocak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:01:03 by yuocak            #+#    #+#             */
/*   Updated: 2025/08/23 16:30:17 by yuocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int					id;
	int					eaten_count;
	long long			last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_philo_data	*data;
}						t_philo;

typedef struct s_philo_data
{
	int					number_philo;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					must_eat_count;
	long long			start_time;
	int					simulation_running;
	int					all_eaten;
	pthread_t			monitor_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		meal_lock;
	t_philo				*philos;
}						t_philo_data;

int						check_arguments(int argc, char **argv,
							t_philo_data *data);
char					*ft_strtrim(const char *s1, const char *set);
int						init_data(t_philo_data *data);
void					clean_mutex(t_philo_data *data);
int						ft_atoi(const char *str);
int						start_sim(t_philo_data *data);
long long				get_time(void);

void					print_status(t_philo *philo, char *message);
int						forks_avail(t_philo *philo);
void					sensitive_sleep(t_philo_data *philo,
							long long sleep_time);

void					eating(t_philo *philo);
void					think(t_philo *philo);
void					sleeping(t_philo *philo);
#endif