/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 11:17:06 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/05 13:49:18 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	print_status(t_coders *coder, char *status, int force)
{
	pthread_mutex_lock(&coder->table_link->mutex_print);
	pthread_mutex_lock(&coder->table_link->mutex_stop);
	if (force || !coder->table_link->stop)
	{
		pthread_mutex_unlock(&coder->table_link->mutex_stop);
		printf("%ld %d %s\n", get_time(coder->data), coder->n, status);
	}
	else
		pthread_mutex_unlock(&coder->table_link->mutex_stop);
	pthread_mutex_unlock(&coder->table_link->mutex_print);
}

void	coders_compile(t_parse_data *data, t_coders *coder)
{
	take_dongle(coder);
	print_status(coder, "is compiling", 0);
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile_time = get_time(data);
	coder->compile_nb++;
	pthread_mutex_unlock(&coder->mutex);
	ft_usleep(data->time_to_compile, coder);
	release_dongles(coder);
}

void	coders_debug(t_parse_data *data, t_coders *coder)
{
	print_status(coder, "is debugging", 0);
	ft_usleep(data->time_to_debug, coder);
}

void	coders_refactor(t_parse_data *data, t_coders *coder)
{
	print_status(coder, "is refactoring", 0);
	ft_usleep(data->time_to_refactor, coder);
}

void	*coders_routine(void *args)
{
	t_coders	*coder;

	coder = (t_coders *)args;
	if (coder->n % 2 == 0)
		ft_usleep(100, coder);
	while (!is_terminated(coder->table_link) && coder->compile_nb
		< coder->data->number_of_compiles_required)
	{
		coders_compile(coder->data, coder);
		coders_debug(coder->data, coder);
		coders_refactor(coder->data, coder);
	}
	pthread_mutex_lock(&coder->mutex_finish);
	coder->is_finish = 1;
	pthread_mutex_unlock(&coder->mutex_finish);
	return (NULL);
}
