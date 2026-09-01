/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 19:54:24 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/01 21:26:23 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	*death_check(void *args)
{
	int	i;
	long	last;
	t_table	*table = (t_table *)args;
	int	is_stoped;

	pthread_mutex_lock(&table->mutex_stop);
	is_stoped = table->stop;
	pthread_mutex_unlock(&table->mutex_stop);
	while (!is_stoped)
	{
		i = 0;
		while (i < table->data->number_of_coders)
		{
			pthread_mutex_lock(&table->coders[i]->mutex);
			last = table->coders[i]->last_compile_time;
			pthread_mutex_unlock(&table->coders[i]->mutex);
			if (get_time(table->data) - last >= table->data->time_to_burnout)
			{
				pthread_mutex_lock(&table->mutex_stop);
				table->stop = 1;
				pthread_mutex_unlock(&table->mutex_stop);
				print_status(table->coders[i], "burned out");
				break ;
			}
			i++;
		}
		pthread_mutex_lock(&table->mutex_stop);
		is_stoped = table->stop;
		pthread_mutex_unlock(&table->mutex_stop);
		usleep(1000);
	}
	return (NULL);
}

void	check_finish(t_table *table)
{
	int	i;
	int	finish;
	int	is_stoped;

	pthread_mutex_lock(&table->mutex_stop);
	is_stoped = table->stop;
	pthread_mutex_unlock(&table->mutex_stop);
	while (!is_stoped)
	{
		while (i < table->data->number_of_coders)
		{
			pthread_mutex_lock(&table->coders[i]->mutex_finish);
			finish = table->coders[i]->is_finish;
			pthread_mutex_unlock(&table->coders[i]->mutex_finish);
			if (finish)
			{
				pthread_mutex_lock(&table->mutex_stop);
				table->stop = 1;
				pthread_mutex_unlock(&table->mutex_stop);
				return ;
			}
			i++;
		}
		pthread_mutex_lock(&table->mutex_stop);
		is_stoped = table->stop;
		pthread_mutex_unlock(&table->mutex_stop);
	}
}
