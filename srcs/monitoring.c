/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 19:54:24 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/04 19:19:52 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

int	check_death(t_table *table)
{
	long	last;
	int		i;
	int		is_finish;

	i = 0;
	while (i < table->data->number_of_coders)
	{
		pthread_mutex_lock(&table->coders[i]->mutex);
		last = table->coders[i]->last_compile_time;
		pthread_mutex_unlock(&table->coders[i]->mutex);
		pthread_mutex_lock(&table->coders[i]->mutex_finish);
		is_finish = table->coders[i]->is_finish;
		pthread_mutex_unlock(&table->coders[i]->mutex_finish);
		if (!is_finish && get_time(table->data) - last
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
	int	is_finish;

	i = 0;
	while (i < table->data->number_of_coders)
	{
		pthread_mutex_lock(&table->coders[i]->mutex_finish);
		is_finish = table->coders[i]->is_finish;
		pthread_mutex_unlock(&table->coders[i]->mutex_finish);
		if (!is_finish)
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
	pthread_mutex_lock(&table->mutex_stop);
	is_stoped = table->stop;
	pthread_mutex_unlock(&table->mutex_stop);
	while (!is_stoped)
	{
		if (!check_death(table))
			break ;
		if (check_finish(table))
			break ;
		pthread_mutex_lock(&table->mutex_stop);
		is_stoped = table->stop;
		pthread_mutex_unlock(&table->mutex_stop);
		usleep(2000);
	}
	return (NULL);
}
