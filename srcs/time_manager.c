/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:51:32 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/02 16:00:16 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

int	set_start_time(t_parse_data *data)
{
	if (gettimeofday(&(data->tv), NULL))
		return (0);
	return (1);
}

time_t	get_time(t_parse_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec - data->tv.tv_sec) * 1000 + (time.tv_usec - data->tv.tv_usec) / 1000);
}

void	ft_usleep(long time_to_wait, t_coders *coder)
{
	int	is_stoped;
	int	remaining;
	int	first_wait;
	int	i;

	i = 0;
	remaining = time_to_wait % 100;
	first_wait = time_to_wait - remaining;
	pthread_mutex_lock(&coder->table_link->mutex_stop);
	is_stoped = coder->table_link->stop;
	pthread_mutex_unlock(&coder->table_link->mutex_stop);
	while (!is_stoped && i != first_wait)
	{
		usleep(100000);
		pthread_mutex_lock(&coder->table_link->mutex_stop);
		is_stoped = coder->table_link->stop;
		pthread_mutex_unlock(&coder->table_link->mutex_stop);
		i += 100;
	}
	if (!is_stoped)
		usleep(remaining);
}

