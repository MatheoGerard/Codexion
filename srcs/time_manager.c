/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:51:32 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 16:05:53 by mgerard          ###   ########.fr       */
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
	return ((time.tv_sec - data->tv.tv_sec) * 1000
		+ (time.tv_usec - data->tv.tv_usec) / 1000);
}

void	ft_usleep(long time_to_wait, t_coders *coder)
{
	int	remaining;
	int	first_wait;
	int	i;

	i = 0;
	remaining = time_to_wait % 100;
	first_wait = time_to_wait - remaining;
	while (!is_terminated(coder->table_link) && i != first_wait)
	{
		usleep(100000);
		i += 100;
	}
	if (!is_terminated(coder->table_link))
		usleep(remaining);
}

time_t	get_available_time(t_dongle *dongle)
{
	long long	dongle_time;

	pthread_mutex_lock(&dongle->mutex_time);
	dongle_time = dongle->available;
	pthread_mutex_unlock(&dongle->mutex_time);
	return (dongle_time);
}

time_t	compute_key(t_coders *coder, t_dongle *dongle)
{
	t_parse_data	*data;

	data = coder->table_link->data;
	if (ft_strcmp(dongle->scheduler, "edf") == 0)
		return (coder->last_compile_time + data->time_to_burnout);
	return (get_time(data));
}
