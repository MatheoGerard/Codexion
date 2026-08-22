/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 14:51:32 by mgerard           #+#    #+#             */
/*   Updated: 2026/08/22 13:11:04 by mgerard          ###   ########.fr       */
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

