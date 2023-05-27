/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:10:12 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/27 21:11:39 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_eat(t_data *data, t_thread_config *config)
{
	data->fork_data.fork = 0;
	data->next->fork_data.fork = 0;
	config->die_time = config->now + data->config->die_duration;
	config->state = 2;
	config->state_time = config->now + data->config->eat_duration;
	printf("%lld %d %s", config->now, data->id, PHILO_FORK);
	printf("%lld %d %s", config->now, data->id, PHILO_EAT);
}

void	ft_philo_sleep(t_data *data, t_thread_config *config)
{
	data->fork_data.fork = 1;
	data->fork_data.time = config->now + 1;
	data->next->fork_data.fork = 1;
	data->next->fork_data.time = config->now + 1;
	config->state = 3;
	config->state_time = config->now + 1 + data->config->sleep_duration;
	if (config->should_eat != -1 && config->should_eat != 0)
		config->should_eat--;
	printf("%lld %d %s", config->now + 1, data->id, PHILO_SLEEP);
}

void	ft_philo_decide(t_data *data, t_thread_config *config)
{
	if (config->state == 3 && config->now == config->state_time)
	{
		if (data->fork_data.fork && data->next->fork_data.fork
			&& config->now == data->fork_data.time
			&& config->now == data->next->fork_data.time)
			ft_philo_eat(data, config);
		else
		{
			config->state = 1;
			printf("%lld %d %s", config->now, data->id, PHILO_THINK);
		}
	}
}

void	ft_philo_die(t_data *data, t_thread_config *config)
{
	int	i;
	int	f;

	if (config->die_time == config->now
		&& pthread_mutex_lock(&data->config->ate_lock.mutex) == 0)
	{
		printf("%lld %d %s", config->now, data->id, PHILO_DIE);
		data->config->ate_lock.stop_flag = 1;
		pthread_mutex_unlock(&data->config->ate_lock.mutex);
	}
	if (config->should_eat == 0
		&& pthread_mutex_lock(&data->config->ate_lock.mutex) == 0)
	{
		data->config->ate_lock.ate[data->id - 1] = 1;
		i = -1;
		f = 0;
		while (++i < data->config->count)
		{
			if (data->config->ate_lock.ate[i] == 0)
				f = 1;
		}
		if (f == 0)
			data->config->ate_lock.stop_flag = 1;
		pthread_mutex_unlock(&data->config->ate_lock.mutex);
	}
}