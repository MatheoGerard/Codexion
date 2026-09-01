/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerard <mgerard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/15 11:17:06 by mgerard           #+#    #+#             */
/*   Updated: 2026/09/01 19:41:10 by mgerard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/codexion.h"

void	print_status(t_coders *coder, char *status)
{
	pthread_mutex_lock(&coder->table_link->mutex_print);
	printf("%ld %d %s\n", get_time(coder->data), coder->n, status);
	pthread_mutex_unlock(&coder->table_link->mutex_print);
}

void	coders_compile(t_parse_data *data, t_coders *coder)
{
	take_dongle(coder);
	print_status(coder, "is compiling");
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile_time = get_time(data);
	coder->compile_nb++;
	pthread_mutex_unlock(&coder->mutex);
	usleep(data->time_to_compile * 1000);
	release_dongles(coder);
}

void	coders_debug(t_parse_data *data, t_coders *coder)
{
	print_status(coder, "is debugging");
	coder->compile_nb++;
	usleep(data->time_to_debug * 1000);
}

void	coders_refactor(t_parse_data *data, t_coders *coder)
{
	print_status(coder, "is refactoring");
	usleep(data->time_to_refactor * 1000);
}

void	*coders_routine(void *args)
{
	t_coders	*coder;

	coder = (t_coders *)args;
	if (coder->n % 2 == 0)
		usleep(100);
	while (coder->compile_nb < coder->data->number_of_compiles_required)
	{
		coders_compile(coder->data, coder);
		coders_debug(coder->data, coder);
		coders_refactor(coder->data, coder);
	}
	return (NULL);
}
