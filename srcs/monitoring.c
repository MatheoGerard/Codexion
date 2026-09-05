/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 19:54:24 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 12:08:59 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

int	check_death(t_table *table)
{
	long	last;
	int		i;

	i = 0;
	while (i < table->data->number_of_coders)
	{
		pthread_mutex_lock(&table->coders[i]->mutex);
		last = table->coders[i]->last_compile_time;
		pthread_mutex_unlock(&table->coders[i]->mutex);
		if (!is_completed(table->coders[i]) && get_time(table->data) - last
			>=table->data->time_to_burnout)
		{
			print_status(table->coders[i], "burned out", 1);
			pthread_mutex_lock(&table->mutex_stop);
			table->stop = 1;
			pthread_mutex_unlock(&table->mutex_stop);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_finish(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->number_of_coders)
	{
		if (!is_completed(table->coders[i]))
			return (0);
		i++;
	}
	print_status(table->coders[table->data->number_of_coders - 1],
		"successfully completed", 1);
	pthread_mutex_lock(&table->mutex_stop);
	table->stop = 1;
	pthread_mutex_unlock(&table->mutex_stop);
	return (1);
}

void	*death_check(void *args)
{
	int		is_stoped;
	t_table	*table;

	table = (t_table *)args;
	is_stoped = is_terminated(table);
	while (!is_stoped)
	{
		if (!check_death(table))
			break ;
		if (check_finish(table))
			break ;
		is_stoped = is_terminated(table);
		usleep(2000);
	}
	return (NULL);
}
